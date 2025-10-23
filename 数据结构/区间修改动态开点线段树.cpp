#include <bits/stdc++.h>
using namespace std;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using f64 = long double;
using i128 = __int128_t;
using u128 = __uint128_t;
template<typename Info, typename Tag, typename T = i64>
struct SegmentTree {
    struct Node {
        Node *l = nullptr;
        Node *r = nullptr;
        Info info;
        Tag tag;
    } *root = nullptr;
    T L, R;

    SegmentTree() = default;
    SegmentTree(T n) : L(0), R(n) {}
    SegmentTree(T L, T R) : L(L), R(R) {}

    void apply(Node *id, const Tag &dx) {
        if (id == nullptr) {
            return;
        }
        id->info.apply(dx);
        id->tag.apply(dx);
    }
    void pushup(Node *id) {
        id->info = (id->l == nullptr ? Info() : id->l->info) + (id->r == nullptr ? Info() : id->r->info);
    }
    void pushdown(Node *id) {
        apply(id->l, id->tag);
        apply(id->r, id->tag);
        id->tag = Tag();
    }

    void update(T pos, const Info &val) {
        update(root, L, R, pos, val);
    }
    void update(Node *&id, T l, T r, T pos, const Info &val) {
        if (id == nullptr) {
            id = new Node();
        }
        if (l == r) {
            id->info = val;
            return;
        }
        pushdown(id);
        T mid = l + r >> 1;
        if (pos <= mid) {
            update(id->l, l, mid, pos, val);
        } else {
            update(id->r, mid + 1, r, pos, val);
        }
        pushup(id);
    }
    void rangeUpdate(int l, int r, const Tag &dx) {
        rangeUpdate(root, L, R, l, r, dx);
    }
    void rangeUpdate(Node *&id, int l, int r, int x, int y, const Tag &dx) {
        if (x <= l && r <= y) {
            apply(id, dx);
            return;
        }
        pushdown(id);
        T mid = l + r >> 1;
        if (x <= mid) {
            rangeUpdate(id->l, l, mid, x, y, dx);
        }
        if (y > mid) {
            rangeUpdate(id->r, mid + 1, r, x, y, dx);
        }
        pushup(id);
    }
    Info query(T pos) {
        return rangeQuery(pos, pos);
    }
    Info rangeQuery(T l, T r) {
        return rangeQuery(root, L, R, l, r);
    }
    Info rangeQuery(Node *&id, T l, T r, T x, T y) {
        if (y < l || x > r || id == nullptr) {
            return Info();
        }
        if (x <= l && r <= y) {
            return id->info;
        }
        pushdown(id);
        T mid = l + r >> 1;
        return rangeQuery(id->l, l, mid, x, y) + rangeQuery(id->r, mid + 1, r, x, y);
    }

    void merge(SegmentTree<Info, Tag, T> seg) {
        root = merge(root, seg.root, L, R);
    }
    Node *merge(Node *&xid, Node *&yid, T l, T r) {
        if (xid == nullptr) {
            return yid;
        }
        if (yid == nullptr) {
            return xid;
        }
        if (l == r) {
            xid->info = (xid->info + yid->info);
            return xid;
        }
        pushdown(xid);
        pushdown(yid);
        T mid = l + r >> 1;
        xid->l = merge(xid->l, yid->l, l, mid);
        xid->r = merge(xid->r, yid->r, mid + 1, r);
        pushup(xid);
        return xid;
    }
};

void solve() {

    return;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}