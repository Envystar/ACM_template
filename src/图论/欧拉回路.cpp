#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
// 无向图欧拉回路or通路
struct Euler {
    i64 id = 0;
    vector<i64> edg;           // 存储边
    vector<vector<i64>> graph; // 存储图
    // 初始化
    Euler(i64 n, i64 m) {
        graph.resize(n + 1);
        edg.resize(m + 1);
    }
    // 添加边
    void add_edge(i64 u, i64 v) {
        id++;
        graph[u].push_back(id);
        graph[v].push_back(id);
        edg[id] = u ^ v;
    }
    // 判断是否存在欧拉通路and返回起点
    i64 is_semiEuler() {
        i64 n = graph.size() - 1;
        i64 odd = 0, start = 0;
        for (i64 i = 1; i <= n; i++) {
            if (graph[i].size() & 1) {
                odd++;
                start = i;
            }
        }
        if (odd == 0)
            return 1;
        if (odd == 2)
            return start;
        return 0;
    }
    // 判断是否存在欧拉回路
    bool is_Euler() {
        i64 n = graph.size() - 1;
        for (i64 i = 1; i <= n; i++) {
            if (graph[i].size() & 1)
                return false;
        }
        return true;
    }
    // 求解欧拉回路or通路
    vector<i64> Euler_tour(i64 start) {
        vector<i64> tour;
        function<void(i64)> dfs = [&](i64 u) {
            while (!graph[u].empty()) {
                i64 i = graph[u].back();
                graph[u].pop_back();
                if (edg[i] == -1)
                    continue;
                i64 v = edg[i] ^ u;
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
struct directed_Euler {
    vector<i64> inE, outE;     // 存储入,出度
    vector<vector<i64>> graph; // 存储图
    // 初始化
    directed_Euler(i64 n, i64 m) {
        graph.resize(n + 1);
        inE.resize(n + 1);
        outE.resize(n + 1);
    }
    // 添加边
    void add_edge(i64 u, i64 v) {
        graph[u].push_back(v);
        outE[u]++;
        inE[v]++;
    }
    // 判断是否存在欧拉通路and返回起点
    i64 is_semiEuler() {
        i64 n = graph.size() - 1;
        i64 odd = 0, neodd = 0, start = 0;
        for (i64 i = 1; i <= n; i++) {
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
        i64 n = graph.size() - 1;
        for (i64 i = 1; i <= n; i++) {
            if (inE[i] != outE[i])
                return false;
        }
        return true;
    }
    // 求解欧拉回路or通路
    vector<i64> Euler_tour(i64 start) {
        vector<i64> tour;
        function<void(i64)> dfs = [&](i64 u) {
            while (!graph[u].empty()) {
                i64 v = graph[u].back();
                graph[u].pop_back();
                dfs(v);
            }
            tour.push_back(u);
        };
        dfs(start);
        return tour; // 返回的是逆序的欧拉回路or通路
    }
};