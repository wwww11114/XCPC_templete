#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
// O(V^2*E)
template <typename T>
struct Dinic {
    constexpr static T INF = numeric_limits<T>::max();
    vector<vector<pair<int, int>>> gra;
    vector<T> edg;
    vector<int> dep, cur;
    int n, s, t;

    Dinic() = default;
    Dinic(int n) : n(n), gra(n + 1) {}

    void add_edge(int u, int v, T w) {
        gra[u].emplace_back(v, edg.size());
        edg.push_back(w);
        gra[v].emplace_back(u, edg.size());
        edg.push_back(0);
    }
    T work(int s, int t) {
        this->s = s, this->t = t;
        T ans = 0;
        while (bfs()) {
            cur.assign(n + 1, 0);
            ans += dfs(s, INF);
        }
        return ans;
    }

    bool bfs() {
        dep.assign(n + 1, 0);
        dep[s] = 1;
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (const auto &[v, id] : gra[u]) {
                if (edg[id] && !dep[v]) {
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
        while (cur[u] < gra[u].size()) {
            const auto &[v, id] = gra[u][cur[u]];
            if (edg[id] && dep[v] == dep[u] + 1) {
                T k = dfs(v, min(res, edg[id]));
                edg[id] -= k;
                edg[id ^ 1] += k;
                res -= k;
                if (!res) {
                    return flow;
                }
            }
            cur[u]++;
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