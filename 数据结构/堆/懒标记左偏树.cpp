#include <bits/stdc++.h>
typedef long long i64;
using namespace std;
template <typename T, typename Tag, typename _Compare = less<T>>
struct Leftist_Tree {
    struct Node {
        T val;
        Tag tag;
        int dis;
        Node *ls = nullptr, *rs = nullptr;
        Node(const T &x) : val(x) {}
    };
    _Compare comp;
    size_t sz = 0;
    Node *root = nullptr;

    Leftist_Tree() = default;
    Leftist_Tree(const T &x) : root(new Node(x)) {}

public:
    size_t size() { return sz; }
    bool empty() { return root == nullptr; }
    T top() {
        pushdown(root);
        return root->val;
    }
    void pop() {
        sz--;
        pushdown(root);
        root = merge(root->ls, root->ls);
        return;
    }
    void push(const T &x) {
        sz++;
        root = merge(root, new Node(x));
        return;
    }
    void push(Leftist_Tree &x) {
        sz += x.sz;
        root = merge(root, x.root);
        return;
    }
    void update(const Tag &dx) {
        if (root != nullptr) {
            root->tag.apply(dx);
        }
    }

private:
    int dis(Node *x) { return x ? x->dis : 0; }
    Node *merge(Node *x, Node *y) {
        if (x == nullptr)
            return y;
        if (y == nullptr)
            return x;
        pushdown(x);
        pushdown(y);
        if (comp(y->val, x->val)) {
            swap(x, y);
        }
        x->rs = merge(x->rs, y);
        if (dis(x->ls) < dis(x->rs)) {
            swap(x->ls, x->rs);
        }
        x->dis = dis(x->rs) + 1;
        return x;
    }
    void pushdown(Node *x) {
        if (x == nullptr) {
            return;
        }
        x->val.apply(x->tag);
        if (x->ls) {
            x->ls->tag.apply(x->tag);
        }
        if (x->rs) {
            x->rs->tag.apply(x->tag);
        }
        x->tag = Tag();
        return;
    }
};

struct Tag {
    i64 add = 0;
    Tag() = default;
    Tag(i64 x) : add(x) {}
    void apply(const Tag &dx) {
        add += dx.add;
    }
};

struct Info {
    i64 x = 0;
    Info() = default;
    Info(i64 x) : x(x) {}
    void apply(const Tag &dx) {
        x += dx.add;
    }
    friend constexpr strong_ordering operator<=>(const Info &lhs, const Info &rhs) {
        return lhs.x <=> rhs.x;
    }
};

int main() {
    Leftist_Tree<Info, Tag> lt, rt;
    return 0;
}