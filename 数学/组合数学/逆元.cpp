#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
constexpr int mod = 1e9 + 7;
// 模为质数
i64 qpow(i64 a, i64 b) {
    i64 res = 1;
    while (b) {
        if (b & 1)
            res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
i64 inv(i64 x) {
    return qpow(x, mod - 2);
}
// O(n)求逆元
vector<i64> inv(vector<i64> &a) {
    i64 n = a.size() - 1;
    vector<i64> s(n + 1), sv(n + 1), v(n + 1);
    s[0] = 1;
    for (int i = 1; i <= n; ++i)
        s[i] = s[i - 1] * a[i] % mod;
    sv[n] = qpow(s[n], mod - 2);
    for (int i = n; i >= 1; --i)
        sv[i - 1] = sv[i] * a[i] % mod;
    for (int i = 1; i <= n; ++i)
        v[i] = sv[i] * s[i - 1] % mod;
    return v;
}
