#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
struct Trie {
    // 字符集大小
    constexpr static int H = 26;
    vector<array<int, H>> tree;
    int tot = 0;
    Trie() = default;
    Trie(int n) : tree(n) {}
    void insert(const string &s) {
        int cur = 0;
        for (auto &c : s) {
            int ch = c - 'a';
            if (!tree[cur][ch]) {
                tree[cur][ch] = ++tot;
            }
            cur = tree[cur][ch];
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    return 0;
}