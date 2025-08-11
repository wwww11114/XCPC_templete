#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
template <typename T>
struct Trie {
    constexpr static int B = numeric_limits<T>::digits;
    vector<array<T, 2>> tree;
    vector<int> root;
    int tot = 0, cnt = 0;
    Trie() = default;
    Trie(int n) : tree(B *n), root(n + 1) {}
    void insert(const T &x) {
        int cur = root[cnt];
        root[++cnt] = ++tot;
        for (int i = B - 1; i >= 0; i--) {
            bool bit = (x >> i) & 1;
            tree[tot][bit] = ++tot;
            tree[tot][1 ^ bit] = tree[cur][1 ^ bit];
            cur = tree[cur][bit];
        }
    }
    T queryMax(const T &x) {
        int cur = 0;
        T res = 0;
        for (int i = B - 1; i >= 0; i--) {
            bool bit = (x >> i) & 1;
            if (tree[cur][bit ^ 1]) {
                res |= 1LL << i;
                cur = tree[cur][bit ^ 1];
            } else {
                cur = tree[cur][bit];
            }
        }
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int n, ans = 0;
    cin >> n;
    Trie<int> trie(n);
    cout << trie.tree.size() << "\n";
    // for (int i = 0; i < n; i++) {
    //     int x;
    //     cin >> x;
    //     trie.insert(x);
    //     ans = max(ans, trie.queryMax(x));
    // }
    cout << ans << "\n";
    return 0;
}