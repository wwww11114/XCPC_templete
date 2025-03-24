#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
template <typename T>
struct Trie {
    constexpr static int W = numeric_limits<T>::digits;
    vector<array<T, 2>> tree;
    int tot = 0;
    Trie(int n) : tree(W * n + 1) {}
    void insert(const T &x) {
        int cur = 0;
        for (int i = W - 1; i >= 0; i--) {
            int bit = (x >> i) & 1;
            if (!tree[cur][bit]) {
                tree[cur][bit] = ++tot;
            }
            cur = tree[cur][bit];
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    return 0;
}