#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

struct HLD {
    vector<int> fa, sz, hs, dep, top, in, out, rnk;
    vector<vector<int>> tree;
    const int n;
    int cnt = 0;

    HLD() = default;
    HLD(const int &n) : n(n) {
        fa.resize(n + 1);
        sz.resize(n + 1, 1);
        hs.resize(n + 1, -1);
        dep.resize(n + 1);
        top.resize(n + 1);
        in.resize(n + 1);
        out.resize(n + 1);
        rnk.resize(n + 1);
        tree.resize(n + 1);
    }

    void add_edge(int u, int v) {
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    void add_tree(const vector<vector<int>> &tree_) {
        tree = tree_;
    }
    void init(int root = 1) {
        dfs1(root);
        dfs2(root, root);
    }
    int dist(int u, int v) {
        return dep[u] + dep[v] - 2 * dep[lca(u, v)];
    }
    int lca(int u, int v) {
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]]) {
                swap(u, v);
            }
            u = fa[top[u]];
        }
        return dep[u] < dep[v] ? u : v;
    }
    int kth(int u, int k) {
        if (dep[u] < k) {
            return -1;
        }
        while (k) {
            int t = top[u];
            if (dep[u] - dep[t] + 1 <= k) {
                k -= dep[u] - dep[t] + 1;
                u = fa[t];
            } else {
                return rnk[in[u] - k];
            }
        }
        return rnk[in[u] - k];
    }
    bool isAncestor(int u, int v) {
        return in[u] <= in[v] && out[v] <= out[u];
    }

    map<int, vector<int>> build(vector<int> v) {
        sort(v.begin(), v.end(), [&](const int &x, const int &y) {
            return in[x] < in[y];
        });
        int m = v.size() - 1;
        for (int i = 1; i <= m; ++i) {
            v.push_back(lca(v[i - 1], v[i]));
        }
        sort(v.begin(), v.end(), [&](const int &x, const int &y) {
            return in[x] < in[y];
        });        
        v.erase(unique(v.begin(), v.end()), v.end());
        map<int, vector<int>> vt;
        for (int i = 1; i < v.size(); ++i) {
            vt[lca(v[i - 1], v[i])].push_back(v[i]);
            vt[v[i]].push_back(lca(v[i - 1], v[i]));
        }
        return vt;
    }
private:
    void dfs1(int u) {
        for (const int &v : tree[u]) {
            if (v == fa[u]) {
                continue;
            }
            fa[v] = u;
            dep[v] = dep[u] + 1;
            dfs1(v);
            sz[u] += sz[v];
            if (hs[u] == -1 || sz[v] > sz[hs[u]]) {
                hs[u] = v;
            }
        }
    }
    void dfs2(int u, int tp) {
        top[u] = tp;
        in[u] = ++cnt;
        rnk[cnt] = u;
        if (hs[u] == -1) {
            out[u] = cnt;
            return;
        }
        dfs2(hs[u], tp);
        for (const int &v : tree[u]) {
            if (v == fa[u] || v == hs[u]) {
                continue;
            }
            dfs2(v, v);
        }
        out[u] = cnt;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    return 0;
}