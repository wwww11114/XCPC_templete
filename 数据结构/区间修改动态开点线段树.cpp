#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

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
constexpr i64 INF = 1E18;

struct Tag {
    i64 add = 0;
    Tag(i64 x = 0) : add(x) {}
    void apply(const Tag &dx) {
        add += dx.add;
    }
};

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
