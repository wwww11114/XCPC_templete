#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
struct DSU {
    vector<int> p, sz;
    stack<pair<int &, int>> his;

    DSU() = default;
    DSU(int n) : p(n + 1), sz(n + 1, 1) { iota(p.begin(), p.end(), 0); }

    int size(int x) { return sz[find(x)]; }
    size_t version() { return his.size(); }
    bool same(int x, int y) { return find(x) == find(y); }
    int find(int x) {
        while (x != p[x]) {
            x = p[x];
        }
        return x;
    }
    void back_ver(size_t cur = 0) {
        while (his.size() > cur) {
            auto [x, y] = his.top();
            his.pop();
            x = y;
        }
    }
    void add_edge(int x, int y) { merge(x, y); }

    void change(int &x, int y) {
        if (x != y) {
            his.emplace(&x, x);
            x = y;
        }
    }
    bool merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y)
            return false;
        if (sz[x] < sz[y])
            swap(x, y);
        change(sz[x], sz[x] + sz[y]);
        change(p[y], x);
        return true;
    }
};

struct SegmentTree {
#define ls (id << 1)
#define rs (id << 1 | 1)
    SegmentTree(int n, int m) : n(m), info(m << 2), dsu(n) {}
    void add_edge(int u, int v, int s, int t) {
        add_edge(1, 1, n, u, v, s, t);
        return;
    }
    void work() {
        work(1, 1, n);
        return;
    }
    void add_edge(int id, int l, int r, int u, int v, int s, int t) {
        if (s <= l && r <= t) {
            info[id].emplace_back(u, v);
            return;
        }
        int mid = (l + r) / 2;
        if (s <= mid) {
            add_edge(ls, l, mid, u, v, s, t);
        }
        if (t > mid) {
            add_edge(rs, mid + 1, r, u, v, s, t);
        }
        return;
    }
    void work(int id, int l, int r) {
        size_t ver = dsu.version();
        for (const auto &[x, y] : info[id]) {
            dsu.add_edge(x, y);
        }
        if (l == r) {

        } else {
            int mid = (l + r) / 2;
            work(ls, l, mid);
            work(rs, mid + 1, r);
        }
        dsu.back_ver(ver);
        return;
    }
#undef ls
#undef rs
    const int n;
    DSU dsu;
    std::vector<vector<pair<int, int>>> info;
};

void solve() {
    int n, q;
    cin >> n >> q;
    SegmentTree st(n, q);
    map<pair<int, int>, int> mp;
    for (int i = 1; i <= q; i++) {
        int  u, v;
        cin >> u >> v;
        if (u > v)
            swap(u, v);
        if (mp.contains({u, v})) {
            st.add_edge(u, v, mp[{u, v}], i - 1);
            mp.erase({u, v});
        } else {
            mp[{u, v}] = i;
        }
    }
    for (const auto &[k, s] : mp) {
        const auto [u, v] = k;
        st.add_edge(u, v, s, q);
    }
    st.work();
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