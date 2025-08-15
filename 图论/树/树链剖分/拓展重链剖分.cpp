#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

template <typename Info>
struct HLD {
    vector<vector<int>> tree;
    vector<int> fa, sz, hs, dep, top, in, out, rnk;
    vector<Info> info;
    int n;
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
        info.resize(n + 1);
    }

    void add_edge(int u, int v) {
        tree[u].push_back(v);
        tree[v].push_back(u);
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
            int t = fa[top[u]];
            if (dep[u] - dep[t] <= k) {
                k -= dep[u] - dep[t];
                u = t;
            } else {
                return rnk[in[u] - k];
            }
        }
        return rnk[in[u]];
    }
    bool isAncestor(int u, int v) {
        return in[u] <= in[v] && out[v] <= out[u];
    }
    map<int, vector<int>> build(vector<int> v) {
        auto cmp = [&](const int &x, const int &y) {return in[x] < in[y]; };
        sort(v.begin(), v.end(), cmp);
        int m = v.size() - 1;
        for (int i = 1; i <= m; ++i) {
            v.push_back(lca(v[i - 1], v[i]));
        }
        sort(v.begin(), v.end(), cmp);
        v.erase(unique(v.begin(), v.end()), v.end());
        map<int, vector<int>> vt;
        for (int i = 1; i < v.size(); ++i) {
            vt[lca(v[i - 1], v[i])].push_back(v[i]);
            vt[v[i]].push_back(lca(v[i - 1], v[i]));
        }
        return vt;
    }

    void pointInit(vector<Info> &_info) {
        for (int i = 0; i <= n; i++) {
            info[in[i]] = _info[i];
        }
    }
    void edgeInit(int u, int v, const Info &x) {
        if (dep[u] > dep[v]) {
            swap(u, v);
        }
        info[in[v]] = x;
    }

    template <typename Func, typename Tag>
    void update(int u, const Tag &tag, const Func &func) {
        func(in[u], tag);
    }
    template <typename Func, typename Tag>
    void edgeUpdate(int u, int v, const Tag &tag, const Func &func) {
        if (dep[u] > dep[v]) {
            swap(u, v);
        }
        func(in[v], tag);
    }
    template <typename Func, typename Tag>
    void subtreeUpdate(int u, const Tag &tag, const Func &func, bool edge = false) {
        func(in[u] + edge, out[u], tag);
    }
    template <typename Func, typename Tag>
    void pathUpdate(int u, int v, const Tag &tag, const Func &func, bool edge = false) {
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]]) {
                swap(u, v);
            }
            func(in[top[u]], in[u], tag);
            u = fa[top[u]];
        }
        if (dep[u] > dep[v]) {
            swap(u, v);
        }
        func(in[u] + edge, in[v], tag);
    }

    template <typename Func>
    Info query(int u, const Func &func) {
        return func(in[u], in[u]);
    }
    template <typename Func>
    Info edgeQuery(int u, int v, const Func &func) {
        if (dep[u] > dep[v]) {
            swap(u, v);
        }
        return func(in[v]);
    }
    template <typename Func>
    Info subtreeQuery(int u, const Func &func, bool edge = false) {
        return func(in[u] + edge, out[u]);
    }
    template <typename Func>
    Info pathQuery(int u, int v, const Func &func, bool edge = false) {
        Info res{};
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]]) {
                swap(u, v);
            }
            res = res + func(in[top[u]], in[u]);
            u = fa[top[u]];
        }
        if (dep[u] > dep[v]) {
            swap(u, v);
        }
        res = res + func(in[u] + edge, in[v]);
        return res;
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

template <typename Info, typename Tag>
struct SegmentTree {
#define ls (id << 1)
#define rs (id << 1 | 1)
    SegmentTree() = default;
    SegmentTree(int n) : n(n), info(n << 2), tag(n << 2) {} // 最值操作不可用此初始化
    SegmentTree(const std::vector<Info> &init) : SegmentTree((int)init.size() - 1) {
        auto build = [&](auto self, int id, int l, int r) -> void {
            if (l == r) {
                info[id] = init[l];
                return;
            }
            int mid = (l + r) / 2;
            self(self, ls, l, mid);
            self(self, rs, mid + 1, r);
            pushup(id);
        };
        build(build, 1, 1, n);
    }

    void rangeUpdate(int l, int r, const Tag &dx) {
        rangeUpdate(1, 1, n, l, r, dx);
    }
    void update(int t, const Tag &dx) { rangeUpdate(t, t, dx); }
    Info rangeQuery(int l, int r) { return rangeQuery(1, 1, n, l, r); }
    Info query(int t) { return rangeQuery(t, t); }
    void rangeUpdate(int id, int l, int r, int x, int y, const Tag &dx) {
        if (x <= l && r <= y) {
            apply(id, dx);
            return;
        }
        int mid = (l + r) / 2;
        pushdown(id);
        if (x <= mid) {
            rangeUpdate(ls, l, mid, x, y, dx);
        }
        if (y > mid) {
            rangeUpdate(rs, mid + 1, r, x, y, dx);
        }
        pushup(id);
    }
    Info rangeQuery(int id, int l, int r, int x, int y) {
        if (x <= l && r <= y) {
            return info[id];
        }
        int mid = (l + r) / 2;
        pushdown(id);
        Info res;
        if (x <= mid) {
            res = res + rangeQuery(ls, l, mid, x, y);
        }
        if (y > mid) {
            res = res + rangeQuery(rs, mid + 1, r, x, y);
        }
        return res;
    }

    void apply(int id, const Tag &dx) {
        info[id].apply(dx);
        tag[id].apply(dx);
    }
    void pushup(int id) { info[id] = info[ls] + info[rs]; }
    void pushdown(int id) {
        apply(ls, tag[id]);
        apply(rs, tag[id]);
        tag[id] = Tag();
    }
#undef ls
#undef rs
    int n;
    std::vector<Info> info;
    std::vector<Tag> tag;
};

constexpr i64 INF = 1E18;
struct Tag {
    i64 add = 0;
    Tag() = default;
    Tag(i64 _val) {
        add = _val;
    }
    void apply(const Tag &dx) { add = (add + dx.add); }
};

struct Info {
    i64 sum = 0;
    i64 len = 1;
    Info() = default;
    Info(i64 x) {
        sum = x;
    }
    void apply(const Tag &dx) {
        sum += len * dx.add;
    }
};

Info operator+(const Info &x, const Info &y) {
    Info res{};
    res.sum = x.sum + y.sum;
    res.len = x.len + y.len;
    return res;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int n, q, root;
    cin >> n >> q >> root;
    HLD<Info> hld(n);
    vector<Info> init(n + 1);
    for (int i = 1; i <= n; ++i) {
        int x;
        cin >> x;
        init[i] = Info(x);
    }
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        hld.add_edge(u, v);
    }
    hld.init(root);
    hld.pointInit(init);
    SegmentTree<Info, Tag> seg(hld.info);
    
    while (q--) {
        int opt;
        cin >> opt;
        if (opt == 1) {
            int u, v, x;
            cin >> u >> v >> x;
            hld.pathUpdate(u, v, Tag(x), [&](int l, int r, const Tag &dx) {
                seg.rangeUpdate(l, r, dx);
            });
        } else if (opt == 2) {
            int u, v;
            cin >> u >> v;
            cout << hld.pathQuery(u, v, [&](int l, int r) {
                return seg.rangeQuery(l, r);
            }).sum << '\n';
        } else if (opt == 3) {
            int u, x;
            cin >> u >> x;
            hld.subtreeUpdate(u, Tag(x), [&](int l, int r, const Tag &dx) {
                seg.rangeUpdate(l, r, dx);
            });
        } else if (opt == 4) {
            int u;
            cin >> u;
            cout << hld.subtreeQuery(u, [&](int l, int r) {
                return seg.rangeQuery(l, r);
            }).sum << '\n';
        }
    }
    return 0;
}