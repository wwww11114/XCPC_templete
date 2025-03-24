#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
struct Trie {
    // 字符集大小
    constexpr static int H = 26;
    constexpr static int N = 1e5;
    vector<array<int, H>> tree;
    vector<int> cnt;
    int tot = 0;
    Trie() = default;
    void insert(const string &s) {
        int cur = 0;
        for (auto &c : s) {
            int bit = c - 'a';
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