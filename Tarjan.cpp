#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
// 有向图强连通分量
struct Tarjan {
    vector<vector<i64>> graph;
    vector<i64> dfn, low, scc, stk;
    vector<bool> instk;
    i64 n, m, cnt, scc_cnt;
    // 初始化
    Tarjan(i64 n, i64 m) : n(n), m(m), cnt(0), scc_cnt(0) {
        graph.resize(n + 1);
        dfn.resize(n + 1);
        low.resize(n + 1);
        scc.resize(n + 1);
        instk.resize(n + 1);
    }
    // 添加边
    void add_edge(i64 u, i64 v) { graph[u].push_back(v); }
    // 求解强连通分量
    void solve() {
        function<void(i64)> dfs = [&](i64 u) {
            dfn[u] = low[u] = ++cnt;
            stk.push_back(u);
            instk[u] = true;
            for (i64 v : graph[u]) {
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
                    i64 v = stk.back();
                    stk.pop_back();
                    instk[v] = false;
                    scc[v] = scc_cnt;
                    if (v == u)
                        break;
                }
            }
        };
        for (i64 i = 1; i <= n; i++) {
            if (!dfn[i])
                dfs(i);
        }
    }
};
// 无向图强连通分量
struct Tarjan {
    vector<vector<i64>> graph;
    vector<i64> dfn, low, scc, stk;
    vector<bool> instk;
    i64 n, m, cnt, scc_cnt;
    // 初始化
    Tarjan(i64 n, i64 m) : n(n), m(m), cnt(0), scc_cnt(0) {
        graph.resize(n + 1);
        dfn.resize(n + 1);
        low.resize(n + 1);
        scc.resize(n + 1);
        instk.resize(n + 1);
    }
    // 添加边
    void add_edge(i64 u, i64 v) {
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    // 求解强连通分量
    void solve() {
        function<void(i64, i64)> dfs = [&](i64 u, i64 fa) {
            dfn[u] = low[u] = ++cnt;
            stk.push_back(u);
            instk[u] = true;
            for (i64 v : graph[u]) {
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
                    i64 v = stk.back();
                    stk.pop_back();
                    instk[v] = false;
                    scc[v] = scc_cnt;
                    if (v == u)
                        break;
                }
            }
        };
        for (i64 i = 1; i <= n; i++) {
            if (!dfn[i])
                dfs(i, -1);
        }
    }
};