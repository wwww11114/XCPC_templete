#include <bits/stdc++.h>
using namespace std;
typedef long long i64;

struct ST {
    vector<vector<int>> st;
    vector<vector<int>> gra;
    int n;
    ST(int n) : n(n), gra(n + 1) {
        int k = std::bit_width<unsigned>(n + 1);
        st.resize(k + 1, vector<int>(n + 1));
        for (int i = 1; i <= n; i++) {
            st[0][i] = ++n;
            gra.push_back({i});
        }
        for (int i = 0; i < k; i++) {
            for (int j = 0; j + (1 << (i + 1)) - 1 < gra.size(); ++j) {
                st[i + 1][j] = ++n;
                gra.push_back({st[i][j], st[i][j + (1 << i)]});
            }
        }
    }
    // x -> [l, r]
    void range(int x, int l, int r) {
        int t = __lg(r - l + 1);
        gra[x].push_back(st[t][l]);
        gra[x].push_back(st[t][r + 1 - (1 << t)]);
        return;
    }
};
void solve() {
    i64 n;
    cin >> n;
    return;
}
int main() {
    i64 T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}