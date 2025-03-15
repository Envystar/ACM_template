#include <bits/stdc++.h>
using namespace std;
// 无向图欧拉回路or通路
struct Euler {
    int id = 0;
    vector<int> edg;           // 存储边
    vector<vector<int>> graph; // 存储图
    // 初始化
    Euler(int n, int m) {
        graph.resize(n + 1);
        edg.resize(m + 1);
    }
    // 添加边
    void add_edge(int u, int v) {
        id++;
        graph[u].push_back(id);
        graph[v].push_back(id);
        edg[id] = u ^ v;
    }
    // 判断是否存在欧拉通路and返回起点
    int is_semiEuler() {
        int n = graph.size() - 1;
        int odd = 0, start = 0;
        for (int i = 1; i <= n; i++) {
            if (graph[i].size() & 1) {
                odd++;
                start = i;
            }
        }
        if (odd == 0) return 1;
        if (odd == 2) return start;
        return 0;
    }
    // 判断是否存在欧拉回路
    bool is_Euler() {
        int n = graph.size() - 1;
        for (int i = 1; i <= n; i++) {
            if (graph[i].size() & 1) {
                return false;
            }
        }
        return true;
    }
    // 求解欧拉回路or通路
    vector<int> Euler_tour(int start) {
        vector<int> tour;
        function<void(int)> dfs = [&](int u) {
            while (!graph[u].empty()) {
                int i = graph[u].back();
                graph[u].pop_back();
                if (edg[i] == -1) continue;
                int v = edg[i] ^ u;
                edg[i] = -1;
                dfs(v);
            }
            tour.push_back(u);
        };
        dfs(start);
        return tour;
    }
};
// 有向图欧拉回路or通路
struct Directed_Euler {
    vector<int> inE, outE;     // 存储入,出度
    vector<vector<int>> graph; // 存储图
    int n, m;
    // 初始化
    Directed_Euler(int n, int m) : n(n), m(m) {
        graph.resize(n + 1);
        inE.resize(n + 1);
        outE.resize(n + 1);
    }
    // 添加边
    void add_edge(int u, int v) {
        graph[u].push_back(v);
        outE[u]++;
        inE[v]++;
    }
    // 判断是否存在欧拉通路and返回起点
    int is_semiEuler() {
        int odd = 0, neodd = 0, start = 0;
        for (int i = 1; i <= n; i++) {
            if (outE[i] - inE[i] == 1) {
                odd++;
                start = i;
            } else if (inE[i] - outE[i] == 1) {
                neodd++;
            } else if (inE[i] != outE[i]) {
                return 0;
            }
        }
        if (odd == 1 && neodd == 1) {
            return start;
        }
        if (odd == 0 && neodd == 0) {
            return 1;
        }
        return 0;
    }
    // 判断是否存在欧拉回路
    bool is_Euler() {
        int n = graph.size() - 1;
        for (int i = 1; i <= n; i++) {
            if (inE[i] != outE[i])
                return false;
        }
        return true;
    }
    // 求解欧拉回路or通路
    vector<int> Euler_tour(int start) {
        vector<int> tour;
        function<void(int)> dfs = [&](int u) {
            while (!graph[u].empty()) {
                int v = graph[u].back();
                graph[u].pop_back();
                dfs(v);
            }
            tour.push_back(u);
        };
        dfs(start);
        return tour; // 返回的是逆序的欧拉回路or通路
    }
};