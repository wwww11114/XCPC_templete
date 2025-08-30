#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
// 有向图强连通分量
struct Tarjan {
    vector<vector<int>> graph;
    vector<int> dfn, low, scc, stk;
    vector<bool> instk;
    int n, cnt = 0, scc_cnt = 0;
    // 初始化
    Tarjan(int n) : n(n) {
        graph.resize(n + 1);
        dfn.resize(n + 1);
        low.resize(n + 1);
        scc.resize(n + 1);
        instk.resize(n + 1);
    }
    // 添加边
    void add_edge(int u, int v) { 
        graph[u].push_back(v); 
    }
    void dfs(int u) {
        dfn[u] = low[u] = ++cnt;
        stk.push_back(u);
        instk[u] = true;
        for (int v : graph[u]) {
            if (!dfn[v]) {
                dfs(v);
                low[u] = min(low[u], low[v]);
            } else if (instk[v]) {
                low[u] = min(low[u], dfn[v]);
            }
        }
        if (dfn[u] == low[u]) {
            scc_cnt++;
            while (true) {
                int v = stk.back();
                stk.pop_back();
                instk[v] = false;
                scc[v] = scc_cnt;
                if (v == u) {
                    break;
                }
            }
        }
    }
    // 求解强连通分量
    void work() {
        for (int i = 1; i <= n; i++) {
            if (!dfn[i]) {
                dfs(i);
            }
        }
    }
};
// 无向图割边
struct Tarjan {
    vector<vector<pair<int, int>>> graph;
    vector<int> dfn, low, scc, stk;
    vector<bool> instk;
    int n, cnt = 0, scc_cnt = 0, id = 0;
    // 初始化
    Tarjan(int n) : n(n) {
        graph.resize(n + 1);
        dfn.resize(n + 1);
        low.resize(n + 1);
        scc.resize(n + 1);
        instk.resize(n + 1);
    }
    // 添加边
    void add_edge(int u, int v) {
        id++;
        graph[u].push_back({v, id});
        graph[v].push_back({u, id});
    }
    void dfs(int u, int fid) {
        dfn[u] = low[u] = ++cnt;
        stk.push_back(u);
        instk[u] = true;
        for (auto [v, id] : graph[u]) {
            if (id == fid) {
                continue;
            }
            if (!dfn[v]) {
                dfs(v, id);
                low[u] = min(low[u], low[v]);
            } else if (instk[v]) {
                low[u] = min(low[u], dfn[v]);
            }
        }
        if (dfn[u] == low[u]) {
            scc_cnt++;
            while (true) {
                int v = stk.back();
                stk.pop_back();
                instk[v] = false;
                scc[v] = scc_cnt;
                if (v == u) {
                    break;
                }
            }
        }
    };
    // 求解强连通分量
    void solve() {
        for (int i = 1; i <= n; i++) {
            if (!dfn[i]) {
                dfs(i, -1);
            }
        }
    }
};