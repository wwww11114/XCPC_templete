#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
constexpr i64 INF = 1e18;
// O(V*E^2)
template <typename T>
struct EK {
    vector<vector<pair<int, int>>> gra;
    vector<T> edg, flow;
    vector<pair<int, int>> lst;
    int n, m = 0, s, t;

    EK() = default;
    EK(int n) : n(n) , gra(n + 1), lst(n + 1), flow(n + 1) {}

    void add_edge(int u, int v, T w) {
        gra[u].push_back({v, m++});
        edg.push_back(w);
        gra[v].push_back({u, m++});
        edg.push_back(0);
    }
    T work(int s, int t) {
        this->s = s, this->t = t;
        T ans = 0;
        while (bfs()) {
            int v, id;
            ans += flow[t];
            for (int u = t; u != s; u = v) {
                tie(v, id) = lst[u];
                edg[id] -= flow[t];
                edg[id ^ 1] += flow[t];
            }
        }
        return ans;
    }
    
    bool bfs() {
        lst.assign(n + 1, {-1, -1});
        flow.assign(n + 1, 0);
        flow[s] = INF;
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (u == t) {
                return true;
            }
            for (const auto &[v, id] : gra[u]) {
                if (edg[id] && lst[v] == make_pair(-1, -1)) {
                    lst[v] = {u, id};
                    flow[v] = min(flow[u], edg[id]);
                    q.push(v);
                }
            }
        }
        return false;
    }
};

void solve() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    EK<i64> ek(n);
    for (i64 i = 0; i < m; i++) {
        i64 u, v, w;
        cin >> u >> v >> w;
        ek.add_edge(u, v, w);
    }
    cout << ek.work(s, t) << '\n';
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