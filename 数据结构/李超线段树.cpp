#include <bits/stdc++.h>
using namespace std;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using f64 = long double;
using i128 = __int128_t;
using u128 = __uint128_t;
constexpr i64 INF = 1e9;

template <typename Info, typename _Compare = less<i64>>
struct SegmentTree {
#define ls (id << 1)
#define rs (id << 1 | 1)
    int L, R;
    vector<Info> info;
    _Compare comp;

    SegmentTree() = default;
    SegmentTree(int l, int r) : L(l), R(r), info(r - l + 1 << 2) {}
    SegmentTree(int n) : SegmentTree(0, n) {}

    void rangeUpdate(int l, int r, Info val) {
        rangeUpdate(1, L, R, l, r, val);
    }
    void rangeUpdate(int id, int l, int r, int x, int y, Info val) {
        int mid = l + r >> 1;
        if (x <= l && r <= y) {
            if (comp(info[id][mid], val[mid])) {
                swap(info[id], val);
            }
            if (l == r) {
                return;
            }
            if (comp(info[id][l], val[l])) {
                rangeUpdate(ls, l, mid, x, y, val);
            } 
            if (comp(info[id][r], val[r])) {
                rangeUpdate(rs, mid + 1, r, x, y, val);
            }
            return;
        }
        if (x <= mid) {
            rangeUpdate(ls, l, mid, x, y, val);
        }
        if (y > mid) {
            rangeUpdate(rs, mid + 1, r, x, y, val);
        }
    }

    Info query(int pos) {
        return rangeQuery(1, L, R, pos);
    }
    Info rangeQuery(int id, int l, int r, int pos) {
        if (l == r) {
            return info[id];
        }
        Info res;
        int mid = l + r >> 1;
        if (pos <= mid) {
            res = rangeQuery(ls, l, mid, pos);
        } else {
            res = rangeQuery(rs, mid + 1, r, pos);
        }
        if (comp(res[pos], info[id][pos])) {
            res = info[id];
        }
        return res;
    }
#undef ls
#undef rs
};

struct Info {
    f64 k = 0, b = -INF;
    int id = 0;
    Info() = default;
    Info(i64 _k, i64 _b, int _id) : k(_k), b(_b), id(-_id) {}
    Info(i64 x1, i64 y1, i64 x2, i64 y2, int _id) : id(-_id) {
        if (x1 == x2) {
            b = max(y1, y2);
            return;
        }
        k = (f64)(y1 - y2) / (x1 - x2);
        b = y1 - k * x1;
    }

    f64 operator[](i64 x) {
        return k * x + b;
    }
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int q;
    cin >> q;
    int lastans = 0, id = 0;
    SegmentTree<Info> seg(4e4);
    for (int i = 1; i <= q; i++) {
        int op;
        cin >> op;
        if (op == 1) {
            i64 x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            x1 = (x1 + lastans - 1) % 39989 + 1;
            x2 = (x2 + lastans - 1) % 39989 + 1;
            y1 = (y1 + lastans - 1) % 1000000000 + 1;
            y2 = (y2 + lastans - 1) % 1000000000 + 1;
            if (x1 > x2) {
                swap(x1, x2);
                swap(y1, y2);
            }
            seg.rangeUpdate(x1, x2, Info(x1, y1, x2, y2, ++id));
        } else {
            int x;
            cin >> x;
            x = (x + lastans - 1) % 39989 + 1;
            lastans = -seg.query(x).id;
            cout << lastans << '\n';
        }
    }
    return 0;
}