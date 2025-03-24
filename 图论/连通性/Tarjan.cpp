#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
// 有向图强连通分量
struct Tarjan {
    vector<vector<int>> graph;
    vector<int> dfn, low, scc, stk;
    vector<bool> instk;
    int n, m, cnt = 0, scc_cnt = 0;
    // 初始化
    Tarjan(int n, int m) : n(n), m(m) {
        graph.resize(n + 1);
        dfn.resize(n + 1);
        low.resize(n + 1);
        scc.resize(n + 1);
        instk.resize(n + 1);
    }
    // 添加边
    void add_edge(int u, int v) { graph[u].push_back(v); }
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
            while (1) {
                int v = stk.back();
                stk.pop_back();
                instk[v] = false;
                scc[v] = scc_cnt;
                if (v == u)
                    break;
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
    vector<vector<int>> graph;
    vector<int> dfn, low, scc, stk;
    vector<bool> instk;
    int n, m, cnt = 0, scc_cnt = 0;
    // 初始化
    Tarjan(int n, int m) : n(n), m(m) {
        graph.resize(n + 1);
        dfn.resize(n + 1);
        low.resize(n + 1);
        scc.resize(n + 1);
        instk.resize(n + 1);
    }
    // 添加边
    void add_edge(int u, int v) {
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    void dfs(int u, int fa) {
        dfn[u] = low[u] = ++cnt;
        stk.push_back(u);
        instk[u] = true;
        for (int v : graph[u]) {
            if (v == fa)
                continue;
            if (!dfn[v]) {
                dfs(v, u);
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
                if (v == u)
                    break;
            }
        }
    };
    // 求解强连通分量
    void solve() {
        for (int i = 1; i <= n; i++) {
            if (!dfn[i])
                dfs(i, -1);
        }
    }
};