#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
template <typename T>
struct Fenwick {
    vector<T> sum1, sum2;
    int n;
    Fenwick() = default;
    Fenwick(int n) : n(n + 1), sum1(n + 2), sum2(n + 2) {}
    Fenwick(const vector<T> &v) : n(v.size()), sum1(n + 1), sum2(n + 1) {
        for (int i = 0; i <= n; i++) {
            add(i, v[i]);
        }
    }
    void Add(int p, T x) {
        for (int i = p; i <= n; i += i & -i)
            sum1[i] += x, sum2[i] += x * p;
    }
    T Ask(int p) {
        T res = 0;
        for (int i = p; i; i -= i & -i)
            res += (p + 1) * sum1[i] - sum2[i];
        return res;
    }
    void range_add(int l, int r, T x) { Add(l + 1, x), Add(r + 2, -x); }
    void add(int p, T x) { return range_add(p, x, x); };
    i64 range_ask(int l, int r) { return Ask(r + 1) - Ask(l); }
    T ask(int p) { return range_ask(p, p); }
};
struct SparseTable {
    vector<int> v;
    vector<vector<int>> st;
    SparseTable() = default;

    void init(vector<int> &v_) {
        v = v_;
        int k = __lg(v.size());
        st = vector<vector<int>>(k + 1, vector<int>(v.size()));
        iota(st[0].begin(), st[0].end(), 0);
        for (int i = 0; i < k; ++i) {
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
    int n, cnt = 0, tot = 0;
    vector<pair<int, int>> cur;
    vector<vector<int>> tree;
    vector<int> et_dep, id, et, fa;
    SparseTable st;

    Euler_tours() = default;

    Euler_tours(int n) : n(n), id(n + 1), fa(n + 1), et_dep(2 * n), et(2 * n) {}

    void dfs(int u, int dep) {
        id[u] = ++cnt;
        et[cnt] = u;
        et_dep[cnt] = dep;
        cur[u].first = ++tot;
        for (auto v : tree[u]) {
            if (v != fa[u]) {
                fa[v] = u;
                dfs(v, dep + 1);
                et[++cnt] = u;
                et_dep[cnt] = dep;
            }
        }
        cur[u].second = tot;
        return;
    }

    void init(int root = 1) {
        dfs(root, 1);
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
template <typename T>
struct Tree : Euler_tours {
    Fenwick<T> fenwick;
    
    Tree() = default;
    Tree(int n) {
        Euler_tours(n);
        fenwick = Fenwick(n);
    }
    Tree(const vector<T> &x) : n(x.size() - 1) {
        Euler_tours(n);
        fenwick = Fenwick(x);
    }

    void Update(int u, T x) {
        add(u, x - ask(u));
    }
    void add(int u, T x) {
        fenwick.range_add(cur[u].first, cur[u].first, x);
    }
    void Subtree_add(int u, T x) {
        fenwick.range_add(cur[u].first, cur[u].second, x);
    }
    T ask(int u) {
        return fenwick.ask(cur[u].first, cur[u].first);
    }
    T Subtree_ask(int u) {
        return fenwick.range_ask(cur[u].first, cur[u].second);
    }
    int Father(int u) {
        return fa[u];
    }
};

void solve() {
    i64 n;
    cin >> n;
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