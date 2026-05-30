#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;

struct Tarjan {
    vector<vector<int>> graph, vcc;
    vector<int> dfn, low, stk;
    int n, cnt = 0, vcc_cnt = 0;

    Tarjan(int n) : n(n) {
        graph.resize(n + 1);
        dfn.resize(n + 1);
        low.resize(n + 1);
        vcc.resize(n + 1);
    }

    void add_edge(int u, int v) {
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    void dfs(int u, int fa) {
        dfn[u] = low[u] = ++cnt;
        stk.push_back(u);
        int sz = 0;
        for (auto v : graph[u]) {
            if (!dfn[v]) {
                sz++;
                dfs(v, u);
                low[u] = min(low[u], low[v]);
                if (low[v] >= dfn[u]) {
                    vcc_cnt++;
                    while (true) {
                        int num = stk.back();
                        stk.pop_back();
                        vcc[num].push_back(vcc_cnt);
                        if (num == v) {
                            break;
                        }
                    }
                    vcc[u].push_back(vcc_cnt);
                }
            } else if (v != fa) {
                low[u] = min(low[u], dfn[v]);
            }
        }
        if (fa == -1 && sz == 0) {
            vcc_cnt++;
            vcc[u].push_back(vcc_cnt);
            stk.pop_back();
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
    vector<vector<int>> vcc(tar.vcc_cnt + 1);
    for (int i = 1; i <= n; i++) {
        for (auto vcc_id : tar.vcc[i]) {
            vcc[vcc_id].push_back(i);
        }
    }
    cout << tar.vcc_cnt << "\n";
    for (int i = 1; i <= tar.vcc_cnt; i++) {
        cout << vcc[i].size() << " ";
        for (auto u : vcc[i]) {
            cout << u << " ";
        }
        cout << "\n";
    }
}