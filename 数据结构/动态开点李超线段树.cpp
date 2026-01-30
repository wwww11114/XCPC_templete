#include <bits/stdc++.h>
using namespace std;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using f64 = long double;
using i128 = __int128_t;
using u128 = __uint128_t;
constexpr i64 INF = 1e9;

template <typename Info, typename T = i64, typename _Compare = less<i64>>
struct SegmentTree {
    struct Node {
        Node *l = nullptr;
        Node *r = nullptr;
        Info info;
    } *root = nullptr;
    T L, R;
    _Compare comp;

    SegmentTree() = default;
    SegmentTree(T l, T r) : L(l), R(r) {}
    SegmentTree(T n) : SegmentTree(0, n) {}

    void rangeUpdate(T l, T r, Info val) {
        rangeUpdate(root, L, R, l, r, val);
    }
    void rangeUpdate(Node *&id, T l, T r, T x, T y, Info val) {
        if (id == nullptr) {
            id = new Node();
        }
        T mid = l + r >> 1;
        if (x <= l && r <= y) {
            if (comp(id->info[mid], val[mid])) {
                swap(id->info, val);
            }
            if (l == r) {
                return;
            }
            if (comp(id->info[l], val[l])) {
                rangeUpdate(id->l, l, mid, x, y, val);
            } 
            if (comp(id->info[r], val[r])) {
                rangeUpdate(id->r, mid + 1, r, x, y, val);
            }
            return;
        }
        if (x <= mid) {
            rangeUpdate(id->l, l, mid, x, y, val);
        }
        if (y > mid) {
            rangeUpdate(id->r, mid + 1, r, x, y, val);
        }
    }

    Info query(T pos) {
        return rangeQuery(root, L, R, pos);
    }
    Info rangeQuery(Node *&id, T l, T r, T pos) {
        if (id == nullptr) {
            return Info();
        }
        if (l == r) {
            return id->info;
        }
        Info res;
        T mid = l + r >> 1;
        if (pos <= mid) {
            res = rangeQuery(id->l, l, mid, pos);
        } else {
            res = rangeQuery(id->r, mid + 1, r, pos);
        }
        if (comp(res[pos], id->info[pos])) {
            res = id->info;
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

    pair<f64, int> operator[](i64 x) {
        return make_pair(k * x + b, id);
    }
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int q;
    cin >> q;
    int lastans = 0, id = 0;
    SegmentTree<Info, i64, less<pair<f64, int>>> seg(1e5);
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