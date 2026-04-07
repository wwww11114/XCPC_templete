#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
struct SegmentTree {
    int n;
    std::vector<int> in, out;
    std::vector<std::vector<std::pair<int, int>>> v;
#define ls (id<<1)
#define rs (id<<1|1)
    SegmentTree(int n) : n(n), in(n << 2), out(n << 2), v(n * 7) {
        int tot = n;
        auto build = [&](auto self, int id, int l, int r) ->void {
            if (l == r) {
                in[id] = out[id] = l;
                return;
            }
            int mid = (l + r) / 2;
            self(self, ls, l, mid);
            self(self, rs, mid + 1, r);
            in[id] = ++tot;
            out[id] = ++tot;
            update(in[id], in[ls], 0);
            update(in[id], in[rs], 0);
            update(out[ls], out[id], 0);
            update(out[rs], out[id], 0);
        };
        build(build, 1, 1, n);
    }
    void update(int x, int y, int w) { //连一条从x 到 y的边，边权为w
        v[x].emplace_back(y, w);
    }
    //model == 0 时, 从pos 到 [x, y]连边，边权为w
    //model == 1 时, 从[x, y] 到 pos连边，边权为w
    void rangeUpdate(int pos, int x, int y, int w, int model) {
        rangeUpdate(1, 1, n, pos, x, y, w, model);
    }
    void rangeUpdate(int id, int l, int r, int pos, int x, int y, int w, int model) {
        if (x <= l && r <= y) {
            if (model == 0) {
                update(pos, in[id], w);
            } else {
                update(out[id], pos, w);
            }
            return;
        }
        int mid = (l + r) / 2;
        if (x <= mid) {
            rangeUpdate(ls, l, mid, pos, x, y, w, model);
        }
        if (y > mid) {
            rangeUpdate(rs, mid + 1, r, pos, x, y, w, model);
        }
    }
#undef ls
#undef rs
};