#include <bits/stdc++.h>
using namespace std;
typedef long long i64;

template <typename T, int B = numeric_limits<T>::digits>
struct Trie {
    vector<array<T, 2>> tree;
    int tot = 0;
    Trie() = default;
    Trie(int n) : tree(B * n) {}
    void insert(const T &x) {
        int cur = 0;
        for (int i = B - 1; i >= 0; i--) {
            bool bit = (x >> i) & 1;
            if (!tree[cur][bit]) {
                tree[cur][bit] = ++tot;
            }
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
    return 0;
}