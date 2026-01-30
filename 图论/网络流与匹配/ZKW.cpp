#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
// 流量大, 费用范围小的图, 增广路径短的图 (二分图)
template <typename T>
struct ZKW {
    constexpr static T INF = numeric_limits<T>::max();
    vector<vector<int>> gra;
    vector<tuple<int, T, T>> edg;
    vector<T> dis;
    vector<int> cur;
    vector<bool> vis;
    T Maxflow, Mincost;
    int n, s, t;

    ZKW() = default;

    ZKW(int n) : n(n), gra(n + 1) {}

    void add_edge(int u, int v, T cap, T cost) {
        gra[u].push_back(edg.size());
        edg.emplace_back(v, cap, cost);
        gra[v].push_back(edg.size());
        edg.emplace_back(u, 0, -cost);
    }

    pair<T, T> work(int s, int t) {
        this->s = s, this->t = t;
        Maxflow = Mincost = 0;
        while (spfa()) {
            do {
                vis.assign(n + 1, 0);
                cur.assign(n + 1, 0);
                Maxflow += dfs(s);
            } while (vis[t]);
        }
        return make_pair(Maxflow, Mincost);
    }

    bool spfa() {
        dis.assign(n + 1, INF);
        vis.assign(n + 1, 0);

        deque<int> q;
        dis[t] = 0;
        vis[t] = 1;
        q.push_back(t);
        
        while (!q.empty()) {
            int u = q.front();
            q.pop_front();
            vis[u] = 0;
            for (auto id : gra[u]) {
                auto &[v, cap, cost] = edg[id];
                auto &[nv, ncap, ncost] = edg[id ^ 1];
                if (ncap && dis[v] > dis[u] - cost) {
                    dis[v] = dis[u] - cost;
                    if (!vis[v]) {
                        vis[v] = 1;
                        !q.empty() && dis[v] < dis[q.front()] ? q.push_front(v) : q.push_back(v);
                    }
                }
            }
        }
        return dis[s] != INF;
    }

    T dfs(int u, T flow = INF) {
        vis[u] = true;
        if (u == t) {
            return flow;
        }
        T res = flow;
        for (int &i = cur[u]; i < gra[u].size(); i++) {
            int id = gra[u][i];
            auto &[v, cap, cost] = edg[id];
            auto &[nv, ncap, ncost] = edg[id ^ 1];
            if (!vis[v] && cap && dis[u] == dis[v] + cost) {
                T k = dfs(v, min(res, cap));
                cap -= k;
                ncap += k;
                res -= k;
                Mincost += k * cost;
                if (!res) {
                    break;
                }
            }
        }
        return flow - res;
    }
};

void solve() {
    i64 n, m, s, t;
    cin >> n >> m >> s >> t;
    ZKW<int> ssp(n);
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