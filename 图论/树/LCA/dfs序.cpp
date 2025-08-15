#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
template <typename T, typename Func = std::function<T(const T &, const T &)>>
struct ST {
    std::vector<std::vector<T>> st;
    Func func;

    ST() = default;
    ST(const std::vector<T> &v, Func func = [](const T &a, const T &b) {
        return std::max(a, b);
    }) : func(std::move(func)) {
        int k = std::bit_width<unsigned>(v.size());
        st.resize(k + 1, std::vector<T>(v.size()));
        st[0] = v;
        for (int i = 0; i < k; ++i) {
            for (int j = 0; j + (1 << (i + 1)) - 1 < v.size(); ++j) {
                st[i + 1][j] = this->func(st[i][j], st[i][j + (1 << i)]);
            }
        }
    }
    T range(int l, int r) {
        int t = std::__lg(r - l + 1);
        return func(st[t][l], st[t][r + 1 - (1 << t)]);
    }

};
struct Tree {
    int n, cnt = 0;
    vector<vector<int>> tree;
    vector<int> fa, dfn;
    ST<int> st;

    Euler_tours() = default;
    Euler_tours(int n) : n(n), fa(n + 1), dfn(n + 1), tree(n + 1) {}

    void add_edge(int u, int v) {
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    void dfs(int u) {
        dfn[u] = ++cnt;
        for (auto v : tree[u]) {
            if (v == fa[u]) {
                continue;
            }
            fa[v] = u;
            dfs(v);
        }
    }

    void init(int root = 1) {
        dfs(root);
        vector<int> p(n + 1);
        for (int i = 1; i <= n; ++i) {
            p[dfn[i]] = fa[i];
        }
        st = ST<int>(p, [&](const int &u, const int &v) {
            return dfn[u] < dfn[v] ? u : v;
        });
    }

    int lca(int u, int v) {
        if (u == v) {
            return u;
        }
        u = dfn[u], v = dfn[v];
        if (u > v) {
            swap(u, v);
        }
        return st.range(u + 1, v);
    }
};

void solve() {
    int n, q, root;
    cin >> n >> q >> root;
    Euler_tours et(n);
    for (i64 i = 1; i < n; i++) {
        i64 u, v;
        cin >> u >> v;
        et.add_edge(u, v);
    }
    et.init(root);
    while (q--) {
        i64 u, v;
        cin >> u >> v;
        cout << et.lca(u, v) << "\n";
    }
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