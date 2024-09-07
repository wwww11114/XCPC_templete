#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
template <typename T> class SparseTable {
    using VT = vector<T>;
    using VVT = vector<VT>;
    using func_type = function<T(const T &, const T &)>;
    VT v;
    VVT ST;

    static T default_func(const T &t1, const T &t2) { return max(t1, t2); }

    func_type op;

  public:
    void init(const vector<T> &v_, func_type _func = default_func) {
        v = v_;
        int len = v.size(), l1 = ceil(log2(len)) + 1;
        ST.assign(len, VT(l1, 0));
        for (int i = 0; i < len; ++i) {
            ST[i][0] = i;
        }
        for (int j = 1; j < l1; ++j) {
            int pj = (1 << (j - 1));
            for (int i = 0; i + pj < len; ++i) {
                if (v[ST[i][j - 1]] < v[ST[i + (1 << (j - 1))][j - 1]]) {
                    ST[i][j] = ST[i][j - 1];
                } else {
                    ST[i][j] = ST[i + (1 << (j - 1))][j - 1];
                }
            }
        }
    }

    T query_id(int l, int r) {
        int lt = r - l + 1;
        int q = floor(log2(lt));
        if (v[ST[l][q]] < v[ST[r - (1 << q) + 1][q]]) {
            return ST[l][q];
        } else {
            return ST[r - (1 << q) + 1][q];
        }
    }
};
struct Euler_tours {
    int n, cnt = 0;
    vector<vector<int>> graph;
    vector<int> et_dep, id, et;
    SparseTable<int> st;
    Euler_tours(int n)
        : n(n), graph(n + 1), id(n + 1), et_dep(2 * n), et(2 * n) {}

    void add_edg(int u, int v) {
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    void dfs(int u, int fa, int dep) {
        et_dep[++cnt] = dep;
        et[cnt] = u;
        id[u] = cnt;
        for (auto v : graph[u]) {
            if (v != fa) {
                dfs(v, u, dep + 1);
                et_dep[++cnt] = dep;
                et[cnt] = u;
            }
        }
        return;
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
        et.add_edg(u, v);
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