#include <bits/stdc++.h>
using namespace std;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using f64 = long double;
using i128 = __int128_t;
using u128 = __uint128_t;

struct Trie {
    constexpr static int B = 26;
    vector<array<int, B>> tree;
    vector<int> fail, val, end;
    int tot = 0, id = 0;
    Trie() = default;
    Trie(int n, int m) : tree(n), fail(n), val(n), end(m) {}
    void insert(const string &s) {
        int cur = 0;
        for (auto &c : s) {
            int ch = c - 'a';
            if (!tree[cur][ch]) {
                tree[cur][ch] = ++tot;
            }
            cur = tree[cur][ch];
        }
        end[id++] = cur;
    }
    void build() {
        queue<int> q;
        for (int i = 0; i < B; i++) {
            if (tree[0][i]) {
                q.push(tree[0][i]);
            }
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i = 0; i < B; i++) {
                if (tree[u][i]) {
                    fail[tree[u][i]] = tree[fail[u]][i];
                    q.push(tree[u][i]);
                } else {
                    tree[u][i] = tree[fail[u]][i];
                }
            }
        }
    }
    void query(const string &s) {
        int cur = 0;
        vector<pair<int, string>> ans;
        for (auto &c : s) {
            int ch = c - 'a';
            cur = tree[cur][ch];
            val[cur]++;
        }
        vector<vector<int>> tree(tot + 1);
        for (int i = 1; i <= tot; i++) {
            tree[fail[i]].push_back(i);
        }
        auto dfs = [&](auto &&dfs, int u) -> void {
            for (auto &v : tree[u]) {
                dfs(dfs, v);
                val[u] += val[v];
            }
        };
        dfs(dfs, 0);
        return;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int n;
    cin >> n;
    vector<string> s(n);
    Trie trie(2e5 + 1, n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
        trie.insert(s[i]);
    }
    string t;
    cin >> t;
    trie.build();
    trie.query(t);
    for (int i = 0; i < n; i++) {
        cout << trie.val[trie.end[i]] << '\n';
    }
    return 0;
}