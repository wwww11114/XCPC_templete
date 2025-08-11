#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
struct SegmentTree {
    struct Node {
        int l = 0, r = 0;
    };
    int n;
    int root1, root2;
    std::vector<Node> node;
    std::vector<std::vector<std::pair<int, int>>> v;
#define ls(x) (node[x].l)
#define rs(x) (node[x].r)
#define nid(x) (x + n + 1)
    SegmentTree() = default;
    SegmentTree(int n) : n(n) {
        auto build = [&](auto self, int l, int r) -> int {
            node.push_back(Node());
            int id = node.size() - 1;
            if (l != r) {
                int mid = (l + r) / 2;
                ls(id) = self(self, l, mid);
                rs(id) = self(self, mid + 1, r);
            }
            return id;
        };
        auto init = [&](auto self, int id, int l, int r, auto addEgde) -> void {
            if (l == r) {
                addEgde(nid(id), l, 0);
                return;
            }
            int mid = (l + r) / 2;
            self(self, ls(id), l, mid, addEgde);
            self(self, rs(id), mid + 1, r, addEgde);
            addEgde(nid(id), nid(ls(id)), 0);
            addEgde(nid(id), nid(rs(id)), 0);
        };
        root1 = build(build, 1, n);
        root2 = build(build, 1, n);
        v.resize(node.size() + n + 1);
        init(init, root1, 1, n, addEgde1);
        init(init, root2, 1, n, addEgde2);
    }
    std::function<void(int, int, int)> addEgde1 =
        [this](int x, int y, int w) -> void { v[x].emplace_back(y, w); };
    std::function<void(int, int, int)> addEgde2 =
        [this](int x, int y, int w) -> void { v[y].emplace_back(x, w); };
    void rangeUpdate1(int from, int l, int r, int w) {
        rangeUpdate(root1, 1, n, l, r, from, w, addEgde1);
    }
    void rangeUpdate2(int to, int l, int r, int w) {
        rangeUpdate(root2, 1, n, l, r, to, w, addEgde2);
    }
    void rangeUpdate(int id, int l, int r, int x, int y, int pos, int w, auto addEgde) {
        if (x <= l && r <= y) {
            addEgde(pos, nid(id), w);
            return;
        }
        int mid = (l + r) / 2;
        if (x <= mid) {
            rangeUpdate(ls(id), l, mid, x, y, pos, w, addEgde);
        }
        if (y > mid) {
            rangeUpdate(rs(id), mid + 1, r, x, y, pos, w, addEgde);
        }
    }
    void update(int x, int y, int w) { addEgde1(x, y, w); }
#undef ls
#undef rs
#undef nid
};