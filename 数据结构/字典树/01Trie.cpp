#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
constexpr int W = 30;
struct Trie {
    vector<array<int, 2>> tree;
    vector<int> cnt;
    int tot = 0;
    Trie(int n) : tree(W * n + 1) {}
    void insert(const i64 &x) {
        int cur = 0;
        for (int i = W; i >= 0; i--) {
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