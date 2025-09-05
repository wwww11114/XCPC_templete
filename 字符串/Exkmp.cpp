#include <bits/stdc++.h>
using namespace std;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using f64 = long double;
using i128 = __int128_t;
using u128 = __uint128_t;

vector<int> Exkmp(const string &s) {
    vector<int> z(s.size());
    for (int i = 1, l = 0, r = 0; i < s.size(); i++) {
        if (i <= r) {
            z[i] = min(r - i + 1, z[i - l]);
        }
        while (i + z[i] < s.size() && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    string s, t;
    cin >> s >> t;
    i64 ans = 0;
    auto z = Exkmp(t + "#" + s);
    z[0] = t.size();
    for (int i = 0; i < t.size(); i++) {
        ans ^= 1ll * (z[i] + 1) * (i + 1);
    }
    cout << ans << '\n';
    ans = 0;
    for (int i = t.size() + 1; i < z.size(); i++) {
        ans ^= 1ll * (i - t.size()) * (z[i] + 1);
    }
    cout << ans << '\n';
    return 0;
}