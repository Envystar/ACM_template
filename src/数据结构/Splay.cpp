#include <bits/stdc++.h>

class SplayTree {
public:
    SplayTree() {
        tr.push_back(Node());
        insert(INF);
        insert(-INF);
    }
    void insert(int t) { //插入值为t的数
        int id = root, fa = 0;
        while(id && tr[id].val != t) {
            fa = id;
            id = tr[id].nxt[t > tr[id].val];
        }
        if(id) {
            tr[id].cnt++;
        } else {
            id = ++size;
            tr[fa].nxt[t > tr[fa].val] = id;
            tr.push_back(Node(fa, t));
        }
        splay(id);
    }
    int get_pre(int t) { //查找t的前驱节点
        find(t);
        int id = root;
        if(tr[id].val < t) return id;
        id = tr[id].nxt[0];
        while(tr[id].nxt[1]) {
            id = tr[id].nxt[1];
        }
        splay(id);
        return id;
    }
    int get_suc(int t) { //查找t的后继节点
        find(t);
        int id = root;
        if(tr[id].val > t) return id;
        id = tr[id].nxt[1];
        while(tr[id].nxt[0]) {
            id = tr[id].nxt[0];
        }
        splay(id);
        return id;
    }
    void find(int t) {  //查找值为t的节点，并将该节点转到根
        int id = root;
        while(tr[id].nxt[t > tr[id].val] && t != tr[id].val) {
            id = tr[id].nxt[t > tr[id].val];
        } 
        splay(id);
    }
    void erase(int t) { //删除值为t的，只删除1个
        int pre = get_pre(t);
        int suc = get_suc(t);
        splay(pre);
        splay(suc, pre);
        int tid = tr[suc].nxt[0];//目标节点
        if(tr[tid].cnt > 1) {
            tr[tid].cnt--;
            splay(tid);          //向上更新其他节点
        } else {
            tr[suc].nxt[0] = 0;
            splay(suc);          //向上更新其他节点
        }
    }
    int get_root() {
        return root;
    }
    int get_rank(int t) { //查一个数t的排名
        insert(t);
        int res = tr[tr[root].nxt[0]].size;
        erase(t);
        return res;
    }
    int get_kth(int t) {   //查找第k个节点编号
        t++;               //有哨兵，所以++
        int id = root;
        while(true) {
            pushdown(id); //向下传递懒标记
            const auto &[x, y] = tr[id].nxt;
            if(tr[x].size + tr[id].cnt < t) {
                t -= tr[x].size + tr[id].cnt;
                id = y;
            } else {
                if(tr[x].size >= t) {
                    id = tr[id].nxt[0];
                } else {
                    return id;
                }
            }
        }
    }
    int get_val(int t) { //查找排名为t的数的数值
        int id = get_kth(t);
        splay(id);
        return tr[id].val;
    }
    void reverse(int l, int r) { //反转区间[l, r]
        l = get_kth(l - 1), r = get_kth(r + 1);
        splay(l, 0), splay(r, l);
        tr[tr[r].nxt[0]].tag ^= 1;
    }
    void output(int id) { //中序遍历
        pushdown(id);
        const auto &[x, y] = tr[id].nxt;
        if(x != 0) output(x);
        if(std::abs(tr[id].val) != INF) {
            std::cout << tr[id].val << ' ';
        }
        if(y) output(y);
    }
    int val(int id) {
        return tr[id].val;
    }
private:
    class Node {
    public:
        Node() {
            nxt = {0, 0};
            lst = val = size = cnt = tag = 0;
        }
        Node(int _lst, int _val) : lst(_lst), val(_val) {
            nxt = {0, 0};
            tag = 0;
            size = cnt = 1;
        }
        std::array<int, 2> nxt; //左右节点[0左, 1右]
        int lst;                //父亲
        int val;                //权值
        int cnt;                //权值数
        int size;               //子树大小
        int tag;                //懒标记[1翻, 0不翻]
    };
    void rotate(int id) { 
        int pid = tr[id].lst, gid = tr[pid].lst;//父节点，爷节点
        int k = (tr[pid].nxt[1] == id);         //判断id是pid的左节点还是右节点
        tr[pid].nxt[k] = tr[id].nxt[k ^ 1];     //将父节点的k号子节点设置为id的k^1号子节点
        tr[tr[id].nxt[k ^ 1]].lst = pid;        //id的k^1号子节点的父节点设为pid
        tr[id].nxt[k ^ 1] = pid;                //id的k^1号子节点设置为pid
        tr[pid].lst = id;                       //pid的父节点设置为id
        tr[id].lst = gid;                       //id的父节点设置为gid
        tr[gid].nxt[tr[gid].nxt[1] == pid] = id;//gid的子节点设为id
        pushup(pid);                            //更新pid
        pushup(id);                             //更新id
    }
    void splay(int id, int t = 0) {//将id旋转到为t的子节点，为0时id为根
        while(tr[id].lst != t) {
            int pid = tr[id].lst, gid = tr[pid].lst;
            if(gid != t) { //非根做双旋
                if((tr[pid].nxt[0] == id) == (tr[gid].nxt[0] == pid)) { //直线式转中
                    rotate(pid);
                } else {   //折线式转中
                    rotate(id);
                }
            }
            rotate(id);
        }
        if(t == 0) root = id;
    }
    void pushup(int id) {
        const auto &[x, y] = tr[id].nxt;
        tr[id].size = tr[x].size + tr[y].size + tr[id].cnt;
    }
    void pushdown(int id) {
        if(tr[id].tag) {
            auto &[x, y] = tr[id].nxt;
            std::swap(x, y);
            tr[x].tag ^= 1;
            tr[y].tag ^= 1;
            tr[id].tag = 0;
        }
    }
    std::vector<Node> tr;
    int root = 0; //根节点编号
    int size = 0; //节点个数
    const int INF = INT_MAX;
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    SplayTree tr;
    for(int i = 1; i <= n; ++i) {
        tr.insert(i);
    }
    for(int i = 1; i <= m; ++i) {
        int l, r;
        std::cin >> l >> r;
        tr.reverse(l, r);
    }
    tr.output(tr.get_root());
    return 0;
}