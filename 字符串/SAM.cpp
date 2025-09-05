#include <bits/stdc++.h>
using namespace std;
using u32 = uint32_t;
using i64 = long long;
using u64 = uint64_t;
using f64 = long double;
using i128 = __int128_t;
using u128 = __uint128_t;

struct SAM {
    static constexpr int B = 26;
    struct Node {
        int len, link, endsum;
        std::array<int, B> next;
        Node() : len{}, link{}, endsum{}, next{} {}
    };
    std::vector<Node> dag;
    SAM() {
        dag.assign(2, Node());
        dag[0].next.fill(1);
        dag[0].len = -1;
    };
    SAM(const string &s) : SAM() {
        dag.reserve(2 * s.size());
        for (int p = 1; auto c : s) {
            p = extend(p, c);
            dag[p].endsum++;
        }
    }
    int newNode() {
        dag.emplace_back();
        return dag.size() - 1;
    }
    int extend(int p, char c, char offset = 'a') {
        return extend(p, c - offset);
    }
    int extend(int p, int c) {
        if (dag[p].next[c]) {
            int q = dag[p].next[c];
            if (dag[q].len == dag[p].len + 1) {
                return q;
            }
            int r = newNode();
            dag[r].len = dag[p].len + 1;
            dag[r].link = dag[q].link;
            dag[r].next = dag[q].next;
            dag[q].link = r;
            while (dag[p].next[c] == q) {
                dag[p].next[c] = r;
                p = dag[p].link;
            }
            return r;
        }
        int cur = newNode();
        dag[cur].len = dag[p].len + 1;
        while (!dag[p].next[c]) {
            dag[p].next[c] = cur;
            p = dag[p].link;
        }
        dag[cur].link = extend(p, c);
        return cur;
    }
};



int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    string s;
    cin >> s;
    SAM sam(s);
    vector<vector<int>> tree(sam.dag.size());
    for (int i = 2; i < sam.dag.size(); i++) {
        tree[sam.dag[i].link].push_back(i);
    }
    auto dfs=[&](auto dfs, int u) -> void {
        for (auto v : tree[u]) {
            dfs(dfs, v);
            sam.dag[u].endsum += sam.dag[v].endsum;
        }
    };
    dfs(dfs, 1);
    i64 ans = 0;
    for (int i = 1; i < sam.dag.size(); i++) {
        if (sam.dag[i].endsum > 1) {
            ans = max(ans, 1ll * sam.dag[i].len * sam.dag[i].endsum);
        }
    }
    cout << ans << '\n';
    return 0;
}