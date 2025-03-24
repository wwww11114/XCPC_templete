#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
struct Hash {
    vector<i64> h1, p1, h2, p2;
    i64 base1 = 31, base2 = 37;
    i64 mod1 = 1e9 + 9, mod2 = 1e9 + 7;
    Hash(string &s) {
        i64 n = s.size();
        h1.resize(n + 1);
        p1.resize(n + 1);
        h2.resize(n + 1);
        p2.resize(n + 1);
        p1[0] = p2[0] = 1;
        for (i64 i = 1; i <= n; i++) {
            p1[i] = (p1[i - 1] * base1) % mod1;
            p2[i] = (p2[i - 1] * base2) % mod2;
        }
        for (i64 i = 1; i <= n; i++) {
            h1[i] = (h1[i - 1] * base1 + s[i - 1]) % mod1;
            h2[i] = (h2[i - 1] * base2 + s[i - 1]) % mod2;
        }
    }
    pair<i64, i64> get(i64 l, i64 r) {
        i64 hash1 = (h1[r + 1] - h1[l] * p1[r - l + 1] % mod1 + mod1) % mod1;
        i64 hash2 = (h2[r + 1] - h2[l] * p2[r - l + 1] % mod2 + mod2) % mod2;
        return {hash1, hash2};
    }
    bool equal(i64 l1, i64 r1, i64 l2, i64 r2) {
        return get(l1, r1) == get(l2, r2);
    }
};
