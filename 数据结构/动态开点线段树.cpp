#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

template<typename Info, typename T = i64>
struct SegmentTree {
    struct Node {
        Node *l = nullptr;
        Node *r = nullptr;
        Info info;
    } *root = nullptr;
    T L, R;
    
    SegmentTree() = default;
    SegmentTree(T n) : L(0), R(n) {}
    SegmentTree(T L, T R) : L(L), R(R) {}

    void pushup(Node *id) {
        id->info = (id->l == nullptr ? Info() : id->l->info) + (id->r == nullptr ? Info() : id->r->info);
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
        T mid = l + r >> 1;
        if (pos <= mid) {
            update(id->l, l, mid, pos, val);
        } else {
            update(id->r, mid + 1, r, pos, val);
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
        T mid = l + r >> 1;
        return rangeQuery(id->l, l, mid, x, y) + rangeQuery(id->r, mid + 1, r, x, y);
    }

    void merge(SegmentTree<Info, T> seg) {
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
        T mid = l + r >> 1;
        xid->l = merge(xid->l, yid->l, l, mid);
        xid->r = merge(xid->r, yid->r, mid + 1, r);
        pushup(xid);
        return xid;
    }

    SegmentTree<Info, T> split(T L, T R) { //分裂出[L, R]的部分
        SegmentTree<Info, T> seg = split(L - 1);
        SegmentTree<Info, T> rem = seg.split(R);
        merge(rem);
        return seg;
    }
    SegmentTree<Info, T> split(T k) { //分裂出(k, ∞]的部分
        SegmentTree<Info, T> seg(L, R);
        seg.root = split(root, L, R, k);
        return seg;
    }
    Node *split(Node *&id, T l, T r, T k) {
        if (id == nullptr || l == r || k >= r) {
            return nullptr;
        }
        Node *nid = new Node();
        if (k < l) {
            swap(nid, id);
            return nid;
        }
        T mid = l + r >> 1;
        if (k > mid) {
            nid->r = split(id->r, mid + 1, r, k);
        } else {
            nid->l = split(id->l, l, mid, k);
            swap(nid->r, id->r);
        }
        pushup(id);
        pushup(nid);
        return nid;
    }
    
    T queryk(T k) { //非通用函数
        return queryk(root, L, R, k);
    }
    T queryk(Node *id, T l, T r, T k) {
        if (id == nullptr || id->info.sum < k) {
            return -1;
        }
        if (l == r) {
            return l;
        }
        T mid = l + r >> 1;
        if (id->l != nullptr && id->l->info.sum >= k) {
            return queryk(id->l, l, mid, k);
        } else if (id->r != nullptr) {
            return queryk(id->r, mid + 1, r, k - (id->l == nullptr ? 0 : id->l->info.sum));
        }
        return -1;
    }
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
    res.mn = min(x.mn, y.mn);
    res.mx = max(x.mx, y.mx);
    res.sum = x.sum + y.sum;
    res.len = x.len + y.len;
    return res;
}
int main() {

}
