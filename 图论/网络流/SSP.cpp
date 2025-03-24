#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
constexpr i64 INF = 1e18;
// O(V*E*F)
struct SSP {
    vector<vector<pair<int, int>>> gra;
    vector<pair<i64, i64>> edg;
    vector<i64> dis;
    vector<int> cur;
    vector<bool> vis;
    i64 cost;
    int n, m = 0, s, t;

    SSP() = default;

    SSP(int n) : n(n), gra(n + 1), cur(n + 1), vis(n + 1), dis(n + 1) {}

    void add_edge(int u, int v, i64 w, i64 c) {
        gra[u].push_back({v, m++});
        edg.push_back({w, c});
        gra[v].push_back({u, m++});
        edg.push_back({0, -c});
    }
    pair<i64, i64> work(int s, int t) {
        this->s = s, this->t = t;
        cost = 0;
        i64 ans = 0;
        while (spfa()) {
            fill(cur.begin(), cur.end(), 0);
            fill(vis.begin(), vis.end(), 0);
            ans += dfs(s);
        }
        return make_pair(ans, cost);
    }
    
    bool spfa() {
        fill(dis.begin(), dis.end(), INF);
        fill(vis.begin(), vis.end(), 0);
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

    i64 dfs(int u, i64 flow = INF) {
        vis[u] = true;
        if (u == t) {
            return flow;
        }
        i64 res = flow;
        while (cur[u] < gra[u].size() && res) {
            const auto &[v, id] = gra[u][cur[u]];
            const auto &[w, c] = edg[id];
            if (!vis[v] && w && dis[v] == dis[u] + c) {
                i64 k = dfs(v, min(res, w));
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
    SSP ssp(n);
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