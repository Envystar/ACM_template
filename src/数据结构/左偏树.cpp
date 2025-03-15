#include <bits/stdc++.h>
using i64 = long long;

template<typename T, typename _Compare = std::less<T>>
struct LeftistHeap {
    struct Node {
        Node(const T &_info) : info(_info){} 
        T info;
        int dis = -1;
        Node *ls = nullptr;
        Node *rs = nullptr;
    };
    LeftistHeap() = default;
    LeftistHeap(Comp _cmp) : cmp(std::move(_cmp)) {}
    Node* merge(LeftistHeap &o) {
        _size += o.size();
        return merge(root, o.root);
    }
    int dis(Node* &node) {
        return node == nullptr ? -1 : node->dis;
    }
    Node* merge(Node* &x, Node* &y) {
        if(x == nullptr) return y;
        if(y == nullptr) return x;
        if(cmp(x->info, y->info)) std::swap(x, y);
        x->rs = merge(x->rs, y);
        if(dis(x->ls) < dis(x->rs)) {
            std::swap(x->ls, x->rs);
        }
        x->dis = dis(x->rs) + 1;
        return x;
    }
    void push(const T &info) {
        Node* new_node = new Node(info);
        root = merge(root, new_node);
        ++_size;
    }
    void pop() {
        Node* temp = root;
        root = merge(root->ls, root->rs);
        delete temp;
        --_size;
    }
    T top() {
        assert(root != nullptr);
        return root->info;
    }
    size_t size() {
        return _size;
    }
    bool empty() {
        return _size == 0;
    }
    _Compare cmp;
    Node* root = nullptr;
    size_t _size = 0;
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    

    return 0;
}