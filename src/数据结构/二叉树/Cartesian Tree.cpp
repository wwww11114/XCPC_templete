#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
template <typename T, typename _Compare = less<T>>
struct Cart_Tree {
    struct Node {
        int ls = 0, rs = 0;
        T val;
        Node() = default;
    };
    int n, root = 0;
    vector<Node> v;
    _Compare comp;

    Cart_Tree() = default;
    Cart_Tree(const vector<T> &a) : n(a.size() - 1), v(n + 1) {
        stack<int> st;
        for (int i = 1; i <= n; i++) {
            v[i].val = a[i];
            while (!st.empty()) {
                const auto &pos = st.top();
                if (comp(a[i], a[pos])) {
                    v[i].ls = pos;
                    st.pop();
                } else {
                    break;
                }
            }
            if (!st.empty()) {
                const auto &pos = st.top();
                v[pos].rs = i;
            } else {
                root = i;
            }
            st.push(i);
        }
    }
    const T operator[](int i) const { return v[i].val; }
    void dfs() {
        dfs(root);
        return;
    }
    void dfs(int u) {
        cout << u << ' ';
        if (v[u].ls) dfs(v[u].ls);
        if (v[u].rs) dfs(v[u].rs);
        return;
    }
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        a[x] = i;
    }
    Cart_Tree<int> ct(a);
    ct.dfs();
    return 0;
}