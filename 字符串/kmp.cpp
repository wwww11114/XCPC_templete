#include <bits/stdc++.h>
using namespace std;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using f64 = long double;
using i128 = __int128_t;
using u128 = __uint128_t;

vector<int> kmp(const string &s) {
    vector<int> pi(s.size());
    for (int i = 1, j = 0; i < s.size(); i++, j = pi[i - 1]) {
        while (j >= 1 && s[i] != s[j]) {
            j = pi[j - 1];
        }
        if (s[i] == s[j]) {
            j++;
        }
        pi[i] = j;
    }
    return pi;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    string s, t;
    cin >> s >> t;
    vector<int> pi = kmp(t + "#" + s);
    for (int i = t.size() + 1; i < pi.size(); i++) {
        if (pi[i] == t.size()) {
            cout << i - 2 * t.size() + 1 << '\n';
        }
    }
    for (int i = 0; i < t.size(); i++) {
        cout << pi[i] << " \n"[i == t.size() - 1];
    }
    return 0;
}