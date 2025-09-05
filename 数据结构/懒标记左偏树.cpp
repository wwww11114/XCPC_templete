#include <bits/stdc++.h>
typedef long long i64;
using namespace std;
template <typename Info, typename Tag, typename _Compare = less<Info>>
struct Leftist_Tree {
    struct Node {
        Info val;
        Tag tag;
        int dis;
        Node *ls = nullptr, *rs = nullptr;
        Node(const Info &x) : val(x) {}
    } *root = nullptr;
    _Compare comp;
    int sz = 0;

    Leftist_Tree() = default;
    Leftist_Tree(const Info &x) : root(new Node(x)) {}

public:
    int size() { return sz; }
    bool empty() { return root == nullptr; }
    Info top() {
        pushdown(root);
        return root->val;
    }
    void pop() {
        sz--;
        pushdown(root);
        root = merge(root->ls, root->rs);
    }
    void push(const Info &x) {
        sz++;
        root = merge(root, new Node(x));
    }
    void push(Leftist_Tree &x) {
        sz += x.sz;
        root = merge(root, x.root);
    }
    void update(const Tag &dx) {
        if (root != nullptr) {
            root->tag.apply(dx);
        }
    }

private:
    int dis(Node *x) { return x == nullptr ? 0 : x->dis; }
    Node *merge(Node *x, Node *y) {
        if (x == nullptr) return y; 
        if (y == nullptr) return x; 
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