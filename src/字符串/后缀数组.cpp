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
            rk[i] = s[i];
        }
        int p = 128;
        vector<int> pre(p + 1);
        for (int i = 0; i < s.size(); i++) {
            pre[rk[i]]++;
        }
        for (int i = 1; i <= p; i++) {
            pre[i] += pre[i - 1];
        }
        for (int i = s.size() - 1; i >= 0; i--) {
            sa[--pre[rk[i]]] = i;
        }
        vector<int> nsa(s.size()), nrk(s.size() << 1);
        for (int w = 1; w < s.size(); w <<= 1) {
            for (int i = (int)s.size() - w, cur = 0; i < s.size(); i++) {
                nsa[cur++] = i;
            }
            for (int i = 0, cur = w; i < s.size(); i++) {
                if (sa[i] >= w) {
                    nsa[cur++] = sa[i] - w;
                }
            }
            vector<int> pre(p + 1);
            for (int i = 0; i < s.size(); i++) {
                pre[rk[i]]++;
            }
            for (int i = 1; i <= p; i++) {
                pre[i] += pre[i - 1];
            }
            for (int i = s.size() - 1; i >= 0; i--) {
                sa[--pre[rk[nsa[i]]]] = nsa[i];
            }
            p = 0;
            for (int i = 0; i < s.size(); i++) {
                if (!i || tie(rk[sa[i]], rk[sa[i] + w]) != tie(rk[sa[i - 1]], rk[sa[i - 1] + w])) {
                    p++;
                }
                nrk[sa[i]] = p;
            }
            swap(rk, nrk);
            if (p == s.size()) {
                break;
            }
        }
        rk.resize(s.size());
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