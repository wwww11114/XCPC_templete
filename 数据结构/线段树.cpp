#include <bits/stdc++.h>
typedef long long i64;

template <typename Info>
struct SegmentTree {
#define ls (id << 1)
#define rs (id << 1 | 1)
    int L, R;
    std::vector<Info> info;
    
    SegmentTree() = default;
    SegmentTree(int l, int r) : L(l), R(r), info(r - l + 1 << 2) {}
    SegmentTree(int n) : SegmentTree(0, n) {}
    SegmentTree(const std::vector<Info> &init) : SegmentTree((int)init.size() - 1) {
        auto build = [&](auto self, int id, int l, int r) -> void {
            if (l == r) {
                info[id] = init[l];
                return;
            }
            int mid = l + r >> 1;
            self(self, ls, l, mid);
            self(self, rs, mid + 1, r);
            pushup(id);
        };
        build(build, 1, L, R);
    }

    void pushup(int id) { 
        info[id] = info[ls] + info[rs]; 
    }

    void update(int pos, const Info &val) { 
        update(1, L, R, pos, val); 
    }
    void update(int id, int l, int r, int pos, const Info &val) {
        if (l == r) {
            info[id] = val;
            return;
        }
        int mid = l + r >> 1;
        if (pos <= mid) {
            update(ls, l, mid, pos, val);
        } else {
            update(rs, mid + 1, r, pos, val);
        }
        pushup(id);
    }
    
    Info query(int pos) { 
        return rangeQuery(pos, pos); 
    }
    Info rangeQuery(int l, int r) { 
        return rangeQuery(1, L, R, l, r); 
    }
    Info rangeQuery(int id, int l, int r, int x, int y) {
        if (x <= l && r <= y) {
            return info[id];
        }
        Info res;
        int mid = l + r >> 1;
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
};

constexpr i64 INF = 1e18;

struct Info {
    i64 mn = INF;
    i64 mx = -INF;
    i64 sum = 0;
    i64 len = 0;
    Info() = default;
    Info(i64 x) : mn(x), mx(x), sum(x), len(1) {}
};

Info operator+(const Info &x, const Info &y) {
    Info res;
    res.mn = std::min(x.mn, y.mn);
    res.mx = std::max(x.mx, y.mx);
    res.sum = x.sum + y.sum;
    res.len = x.len + y.len;
    return res;
}