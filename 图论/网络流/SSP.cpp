#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
template <typename T>
struct SSP {
    vector<vector<pair<int, int>>> gra;
    vector<pair<T, T>> edg;
    vector<T> dis;
    vector<int> cur;
    vector<bool> vis;
    T cost;
    constexpr static T INF = numeric_limits<T>::max();
    int n, m = 0, s, t;

    SSP() = default;

    SSP(int n) : n(n), gra(n + 1), cur(n + 1), vis(n + 1), dis(n + 1) {}

    void add_edge(int u, int v, T w, T c) {
        gra[u].emplace_back(v, m++);
        edg.emplace_back(w, c);
        gra[v].emplace_back(u, m++);
        edg.emplace_back(0, -c);
    }
    
    pair<T, T> work(int s, int t) {
        this->s = s, this->t = t;
        cost = 0;
        T ans = 0;
        while (spfa()) {
            cur.assign(n + 1, 0);
            vis.assign(n + 1, 0);
            ans += dfs(s);
        }
        return make_pair(ans, cost);
    }
    
    bool spfa() {
        dis.assign(n + 1, INF);
        vis.assign(n + 1, 0);
        dis[s] = 0;
        queue<int> q;
        q.push(s);
        vis[s] = 1;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            vis[u] = 0;
            for (const auto &[v, id] : gra[u]) {
                const auto &[w, c] = edg[id];
                if (w && dis[v] > dis[u] + c) {
                    dis[v] = dis[u] + c;
                    if (!vis[v]) {
                        vis[v] = 1;
                        q.push(v);
                    }
                }
            }
        }
        return dis[t] != INF;
    }

    T dfs(int u, T flow = INF) {
        vis[u] = true;
        if (u == t) {
            return flow;
        }
        T res = flow;
        while (cur[u] < gra[u].size() && res) {
            const auto &[v, id] = gra[u][cur[u]];
            const auto &[w, c] = edg[id];
            if (!vis[v] && w && dis[v] == dis[u] + c) {
                T k = dfs(v, min(res, w));
                edg[id].first -= k;
                edg[id ^ 1].first += k;
                res -= k;
                cost += k * c;
                if (!res) {
                    break;
                }
            }
            cur[u]++;
        }
        return flow - res;
    }
};

void solve() {
    i64 n, m, s, t;
    cin >> n >> m >> s >> t;
    SSP<int> ssp(n);
    for (i64 i = 1; i <= m; i++) {
        i64 u, v, w, c;
        cin >> u >> v >> w >> c;
        ssp.add_edge(u, v, w, c);
    }
    auto [ans, cost] = ssp.work(s, t);
    cout << ans << ' ' << cost << '\n';
    return;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    i64 T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}