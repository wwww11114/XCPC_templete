#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
struct SparseTable {
    vector<int> v;
    vector<vector<int>> st;
    SparseTable() = default;

    void init(vector<int> &v_) {
        v = v_;
        int k = bit_width(v.size()) - 1;
        st = vector<vector<int>>(k + 1, vector<int>(v.size()));
        iota(st[0].begin(), st[0].end(), 0);
        for (int i = 0; i < k; i++) {
            for (int j = 0; j + (1 << (i + 1)) - 1 < v.size(); ++j) {
                if (v[st[i][j]] < v[st[i][j + (1 << i)]])
                    st[i + 1][j] = st[i][j];
                else
                    st[i + 1][j] = st[i][j + (1 << i)];
            }
        }
    }

    int query_id(int l, int r) {
        int t = __lg(r - l + 1);
        if (v[st[t][l]] < v[st[t][r + 1 - (1 << t)]])
            return st[t][l];
        else
            return st[t][r + 1 - (1 << t)];
    }
};
struct Euler_tours {
    int n, cnt = 0;
    vector<vector<int>> tree;
    vector<int> et_dep, id, et;
    SparseTable st;

    Euler_tours() = default;
    Euler_tours(int n) : n(n), tree(n + 1), id(n + 1), et_dep(2 * n), et(2 * n) {}

    void add_edge(int u, int v) {
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    void add_tree(const vector<vector<int>> &tree_) {
        tree = tree_;
    }

    void dfs(int u, int fa, int dep) {
        et_dep[++cnt] = dep;
        et[cnt] = u;
        id[u] = cnt;
        for (auto v : tree[u]) {
            if (v != fa) {
                dfs(v, u, dep + 1);
                et_dep[++cnt] = dep;
                et[cnt] = u;
            }
        }
    }

    void init(int root = 1) {
        dfs(root, 0, 1);
        st.init(et_dep);
    }

    int lca(int u, int v) {
        int idu = id[u];
        int idv = id[v];
        if (idu > idv) {
            swap(idu, idv);
        }
        int idlca = st.query_id(idu, idv);
        return et[idlca];
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