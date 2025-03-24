#include <bits/stdc++.h>
using i64 = long long;

template <typename Info>
struct SegmentTree {
    struct Node {
        Node *l = nullptr;
        Node *r = nullptr;
        Info info;
    };
    SegmentTree(i64 n) : n(n) {}

    void pushup(Node *id) {
        id->info = (id->l == nullptr ? Info() : id->l->info) + (id->r == nullptr ? Info() : id->r->info);
    }
    void add(i64 pos, const Info &val) { update(pos, query(pos) + val); }
    void update(i64 pos, const Info &val) { update(root, 1, n, pos, val); }
    Info query(i64 pos) { return rangeQuery(pos, pos); }
    Info rangeQuery(i64 l, i64 r) { return rangeQuery(root, 1, n, l, r); }
    void merge(SegmentTree &other) {
        root = mergeNodes(root, other.root, 1, n);
    }

private:
    void update(Node *&id, i64 l, i64 r, i64 pos, const Info &val) {
        if (id == nullptr)
            id = new Node();
        if (l == r) {
            id->info = val;
            return;
        }
        i64 mid = (l + r) / 2;
        if (pos <= mid) {
            update(id->l, l, mid, pos, val);
        } else {
            update(id->r, mid + 1, r, pos, val);
        }
        pushup(id);
    }

    Info rangeQuery(Node *&id, i64 l, i64 r, i64 x, i64 y) {
        if (y < l || x > r || id == nullptr)
            return Info();
        if (x <= l && r <= y) {
            return id->info;
        }
        i64 mid = (l + r) / 2;
        return rangeQuery(id->l, l, mid, x, y) + rangeQuery(id->r, mid + 1, r, x, y);
    }

    Node *mergeNodes(Node *a, Node *b, i64 l, i64 r) {
        if (a == nullptr) {
            return b;
        }
        if (b == nullptr) {
            return a;
        }
        if (l == r) {
            a->info = a->info + b->info;
            delete b;
        } else {
            i64 mid = (l + r) / 2;
            a->l = mergeNodes(a->l, b->l, l, mid);
            a->r = mergeNodes(a->r, b->r, mid + 1, r);
            pushup(a);
            delete b;
            return a;
        }
        return a;
    }
    i64 n;
    Node *root = nullptr;
};

constexpr i64 INF = 1e18;

struct Info {
    Info() = default;
    Info(i64 val) : val(val) {}
    i64 val = 0;
};

Info operator+(const Info &x, const Info &y) {
    Info res;
    res.val = x.val + y.val;
    return res;
}

Info operator^(const Info &x, const Info &y) {
    Info res;
    res.val = x.val + y.val;
    return res;
}
void solve() {
    int n, q;
    std::cin >> n >> q;
    SegmentTree<Info> st(n);
    for (int i = 1; i <= q; ++i) {
        int opt;
        std::cin >> opt;
        if (opt == 0) {
            int pos, val;
            std::cin >> pos >> val;
            st.update(pos + 1, Info(val));
        } else if (opt == 1) {
            int l, r;
            std::cin >> l >> r;
            std::cout << st.rangeQuery(l + 1, r + 1).val << '\n';
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int T = 1;
    // std::cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}