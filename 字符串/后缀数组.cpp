#include <bits/stdc++.h>
using namespace std;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using f64 = long double;
using i128 = __int128_t;
using u128 = __uint128_t;

struct SuffixArray {
    int n;
    vector<int> sa, rk, lc;
    SuffixArray() = default;
    SuffixArray(const string &s) : n(s.size()), sa(n), lc(n), rk(n << 1) {
        std::iota(sa.begin(), sa.end(), 0);
        ranges::sort(sa, [&](int a, int b) {
            return s[a] < s[b];
        });
        rk[sa[0]] = 1;
        for (int i = 1; i < n; i++) {
            rk[sa[i]] = rk[sa[i - 1]] + (s[sa[i]] != s[sa[i - 1]]);
        }
        vector<int> nsa(n), nrk(n << 1), cnt(n + 1);
        for (int w = 1; rk[sa[n - 1]] < n; w <<= 1) {
            for (int i = n - w, cur = 0; i < n; i++) {
                nsa[cur++] = i;
            }
            for (int i = 0, cur = w; i < n; i++) {
                if (sa[i] >= w) {
                    nsa[cur++] = sa[i] - w;
                }
            }
            ranges::fill(cnt, 0);
            for (int i = 0; i < n; i++) {
                cnt[rk[i]]++;
            }
            for (int i = 1; i < n; i++) {
                cnt[i] += cnt[i - 1];
            }
            for (int i = n - 1; i >= 0; i--) {
                sa[--cnt[rk[nsa[i]]]] = nsa[i];
            }
            nrk[sa[0]] = 1;
            for (int i = 1; i < n; i++) {
                nrk[sa[i]] = nrk[sa[i - 1]] + (tie(rk[sa[i]], rk[sa[i] + w]) != tie(rk[sa[i - 1]], rk[sa[i - 1] + w]));
            }
            swap(rk, nrk);
        }
        rk.resize(n);
        for (int i = 0, j = 0; i < n; i++) {
            if (rk[i] == 0) {
                j = 0;
            } else {
                for (j -= (j > 0); i + j < n && sa[rk[i] - 1] + j < n && s[i + j] == s[sa[rk[i] - 1] + j]; j++);
                lc[rk[i] - 1] = j;
            }
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