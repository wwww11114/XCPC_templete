#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
// O(V^2*E)
template <typename T>
struct Dinic {
    constexpr static T INF = numeric_limits<T>::max();
    vector<vector<int>> gra;
    vector<tuple<int, T>> edg;
    vector<int> dep, cur;
    T Maxflow;
    int n, s, t;

    Dinic() = default;
    Dinic(int n) : n(n), gra(n + 1) {}

    void add_edge(int u, int v, T cap) {
        gra[u].push_back(edg.size());
        edg.emplace_back(v, cap);
        gra[v].push_back(edg.size());
        edg.emplace_back(u, 0);
    }
    T work(int s, int t) {
        this->s = s, this->t = t;
        Maxflow = 0;
        while (bfs()) {
            cur.assign(n + 1, 0);
            Maxflow += dfs(s, INF);
        }
        return Maxflow;
    }

    bool bfs() {
        dep.assign(n + 1, 0);

        queue<int> q;
        dep[s] = 1;
        q.push(s);

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (auto id : gra[u]) {
                auto &[v, cap] = edg[id];
                if (cap && !dep[v]) {
                    dep[v] = dep[u] + 1;
                    q.push(v);
                }
            }
        }
        return dep[t];
    }

    T dfs(int u, T flow) {
        if (u == t) {
            return flow;
        }
        T res = flow;
        for (int &i = cur[u]; i < gra[u].size(); i++) {
            int id = gra[u][i];
            auto &[v, cap] = edg[id];
            auto &[nv, ncap] = edg[id ^ 1];
            if (cap && dep[v] == dep[u] + 1) {
                T k = dfs(v, min(res, cap));
                cap -= k;
                ncap += k;
                res -= k;
                if (!res) {
                    break;
                }
            }
        }
        return flow - res;
    }
};

void solve() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    Dinic<i64> dinic(n);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        dinic.add_edge(u, v, w);
    }
    cout << dinic.work(s, t) << '\n';
    return;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}