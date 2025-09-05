#include <bits/stdc++.h>
using namespace std;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using f64 = long double;
using i128 = __int128_t;
using u128 = __uint128_t;

struct Tree {
    vector<vector<int>> tree, fa;
    vector<int> dep;
    int n, B;
    Tree() = default;
    Tree(int n) : n(n), tree(n + 1), dep(n + 1) {
        B = bit_width<unsigned>(n);
        fa.resize(B + 1, std::vector<int>(n + 1, -1));
    }
    void add_edge(int u, int v) {
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    void init(int root = 1) {
        dfs(root);
    }
    void dfs(int u) {
        for (const auto &v : tree[u]) {
            if (fa[0][u] == v) {
                continue;
            }
            fa[0][v] = u;
            for (int i = 1; i <= B && fa[i - 1][v] != -1; i++) {
                fa[i][v] = fa[i - 1][fa[i - 1][v]];
            }
            dep[v] = dep[u] + 1;
            dfs(v);
        }
    }
    int kth(int u, int k) {
        for (int i = B; i >= 0 && u != -1; i--) {
            if (k >> i & 1) {
                u = fa[i][u];
            }
        }
        return u;
    }
    int lca(int u, int v) {
        if (dep[u] > dep[v]) {
            swap(u, v);
        }
        v = kth(v, dep[v] - dep[u]);
        if (u == v) {
            return u;
        }
        for (int i = B; i >= 0; i--) {
            if (fa[i][u] != fa[i][v]) {
                u = fa[i][u];
                v = fa[i][v];
            }
        }
        return fa[0][u];
    }
    int dist(int u, int v) {
        return dep[u] + dep[v] - 2 * dep[lca(u, v)];
    }
};




int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int n, m, root;
    cin >> n >> m >> root;
    Tree tree(n);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        tree.add_edge(u, v);
    }
    tree.init(root);
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        cout << tree.lca(u, v) << '\n';
    }
    return 0;
}