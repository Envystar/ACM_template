#include <bits/stdc++.h>

//拓扑排序
//https://www.luogu.com.cn/problem/B3644
int main() {
	std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> v(n + 1); //存图
    std::vector<int> d(n + 1); //统计入度数量
    for(int i = 1; i <= n; ++i) { //建图
        int x;
        while((std::cin >> x) && x != 0) {
            v[i].push_back(x);
            d[x]++;
        }
    }
    std::queue<int> q;
    for(int i = 1; i <= n; ++i) {
        if(d[i] == 0) {
            q.push(i); //将入度为0的放入队列
        }
    }
    while(!q.empty()) {
        int id = q.front();
        q.pop();
        std::cout << id << ' '; 
        for(auto &nxt  : v[id]) {
            d[nxt]--; //更新入度数
            if(d[nxt] == 0) { //将入度为0的放入队列
                q.push(nxt);
            }
        }
    }
    return 0;
}