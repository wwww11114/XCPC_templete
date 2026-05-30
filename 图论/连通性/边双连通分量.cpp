#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;

struct Tarjan {
    vector<vector<int>> graph;
    vector<int> dfn, low, ecc, stk;
    vector<bool> instk;
    int n, cnt = 0, ecc_cnt = 0;

    Tarjan(int n) : n(n) {
        graph.resize(n + 1);
        dfn.resize(n + 1);
        low.resize(n + 1);
        ecc.resize(n + 1);
        instk.resize(n + 1);
    }

    void add_edge(int u, int v) {
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    void dfs(int u, int fa) {
        dfn[u] = low[u] = ++cnt;
        stk.push_back(u);
        instk[u] = true;
        for (auto v : graph[u]) {
            if (v == fa) {
                fa = -1;
                continue;
            }
            if (!dfn[v]) {
                dfs(v, u);
                low[u] = min(low[u], low[v]);
            } else if (instk[v]) {
                low[u] = min(low[u], dfn[v]);
            }
        }
        if (dfn[u] == low[u]) {
            ecc_cnt++;
            while (true) {
                int v = stk.back();
                stk.pop_back();
                instk[v] = false;
                ecc[v] = ecc_cnt;
                if (v == u) {
                    break;
                }
            }
        }
    };

    void solve() {
        for (int i = 1; i <= n; i++) {
            if (dfn[i]) {
                continue;
            }
            dfs(i, -1);
        }
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    Tarjan tar(n);
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        tar.add_edge(u, v);
    }
    tar.solve();
    vector<vector<int>> ecc(tar.ecc_cnt + 1);
    for (int i = 1; i <= n; i++) {
        ecc[tar.ecc[i]].push_back(i);
    }
    cout << tar.ecc_cnt << "\n";
    for (int i = 1; i <= tar.ecc_cnt; i++) {
        cout << ecc[i].size() << " ";
        for (auto u : ecc[i]) {
            cout << u << " ";
        }
        cout << "\n";
    }
}