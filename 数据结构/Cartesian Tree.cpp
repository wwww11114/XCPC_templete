#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
template <typename T, typename _Compare = less<T>>
struct Cart_Tree {
    int n, root = 0;
    vector<int> ls, rs;
    _Compare comp;

    Cart_Tree() = default;
    Cart_Tree(const vector<T> &a) : n(a.size() - 1), ls(n + 1), rs(n + 1) {
        stack<int> st;
        for (int i = 1; i <= n; i++) {
            while (!st.empty() && comp(a[i], a[st.top()])) {
                ls[i] = st.top();
                st.pop();
            }
            if (!st.empty()) {
                rs[st.top()] = i;
            } else {
                root = i;
            }
            st.push(i);
        }
    }
    void dfs() {
        dfs(root);
        return;
    }
    void dfs(int u) {
        cout << u << ' ';
        if (ls[u]) dfs(ls[u]);
        if (rs[u]) dfs(rs[u]);
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