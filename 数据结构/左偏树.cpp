#include <bits/stdc++.h>
typedef long long i64;
using namespace std;
template <typename T, typename _Compare = less<T>>
struct Leftist_Tree {
    struct Node {
        T val;
        int dis;
        Node *ls = nullptr, *rs = nullptr;
        Node(const T &x) : val(x) {}
    } *root = nullptr;
    _Compare comp;
    int sz = 0;
    Leftist_Tree() = default;
    Leftist_Tree(const T &x) : root(new Node(x)) {}

public:
    int size() { return sz; }
    T top() { return root->val; }
    bool empty() { return root == nullptr; }
    void pop() {
        sz--;
        root = merge(root->ls, root->rs);
    }
    void push(const T &x) {
        sz++;
        root = merge(root, new Node(x));
    }
    void push(Leftist_Tree &x) {
        sz += x.sz;
        root = merge(root, x.root);
    }

private:
    int dis(Node *x) { return x ? x->dis : 0; }
    Node *merge(Node *x, Node *y) {
        if (x == nullptr) return y;
        if (y == nullptr) return x;
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
};


int main() {
    return 0;
}