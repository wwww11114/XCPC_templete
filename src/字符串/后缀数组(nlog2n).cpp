#include <bits/stdc++.h>
using namespace std;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using f64 = long double;
using i128 = __int128_t;
using u128 = __uint128_t;

struct SuffixArray {
    vector<int> sa, rk;
    SuffixArray() = default;
    SuffixArray(const string &s) : sa(s.size()), rk(s.size() << 1) {
        for (int i = 0; i < s.size(); i++) {
            sa[i] = i;
            rk[i] = s[i];
        }
        vector<int> nrk(s.size() << 1);
        for (int w = 1; w < s.size(); w <<= 1) {
            sort(sa.begin(), sa.end(), [&](int x, int y) {
                return tie(rk[x], rk[x + w]) < tie(rk[y], rk[y + w]);
            });
            for (int i = 0, p = 0; i < s.size(); i++) {
                if (!i || tie(rk[sa[i]], rk[sa[i] + w]) != tie(rk[sa[i - 1]], rk[sa[i - 1] + w])) {
                    p++;
                }
                nrk[sa[i]] = p;
            }
            rk = nrk;
        }
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    string s;
    cin >> s;
    SuffixArray sa(s);
    for (int i = 0; i < s.size(); i++) {
        cout << sa.sa[i] + 1 << " \n"[i == s.size()];
    }
    return 0;
}