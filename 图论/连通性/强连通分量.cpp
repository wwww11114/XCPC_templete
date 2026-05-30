#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;

struct Tarjan {
    vector<vector<int>> graph;
    vector<int> dfn, low, scc, stk;
    vector<bool> instk;
    int n, cnt = 0, scc_cnt = 0;

    Tarjan(int n) : n(n) {
        graph.resize(n + 1);
        dfn.resize(n + 1);
        low.resize(n + 1);
        scc.resize(n + 1);
        instk.resize(n + 1);
    }

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

    void work() {
        for (int i = 1; i <= n; i++) {
            if (dfn[i]) {
                continue;
            }
            dfs(i);
        }
    }
};