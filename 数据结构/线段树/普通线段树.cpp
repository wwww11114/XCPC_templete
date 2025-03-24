#include <bits/stdc++.h>
typedef long long i64;
template <typename Info>
struct SegmentTree {
#define ls (id << 1)
#define rs (id << 1 | 1)
    SegmentTree(int n) : n(n), info(n << 2) {}
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
    void add(int pos, const Info &val) { update(pos, val, [](Info &x, const Info &y) { x = x + y; }); }
    void update(int pos, const Info &val) { update(1, 1, n, pos, val); }
    Info query(int pos) { return rangeQuery(pos, pos); }
    Info rangeQuery(int l, int r) { return rangeQuery(1, 1, n, l, r); }
    void pushup(int id) { info[id] = info[ls] + info[rs]; }
    void update(int id, int l, int r, int pos, const Info &val, funciton<void(Info &, const Info &)> &func) {
        if (l == r) {
            func(info[id], val);
            return;
        }
        int mid = (l + r) / 2;
        if (pos <= mid) {
            update(ls, l, mid, pos, val, func);
        } else {
            update(rs, mid + 1, r, pos, val, func);
        }
        pushup(id);
    }
    Info rangeQuery(int id, int l, int r, int x, int y) {
        if (x <= l && r <= y) {
            return info[id];
        }
        int mid = (l + r) / 2;
        Info res;
        if (x <= mid) {
            res = res + rangeQuery(ls, l, mid, x, y);
        }
        if (y > mid) {
            res = res + rangeQuery(rs, mid + 1, r, x, y);
        }
        return res;
    }
#undef ls
#undef rs
    const int n;
    std::vector<Info> info;
};

struct Info {
    Info() = default;
};

Info operator+(const Info &x, const Info &y) {
    Info res;
    return res;
}