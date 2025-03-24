#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
const int mod = 1e9 + 7;
vector<i64> fac, inv;
i64 qpow(i64 a, i64 b) {
    i64 res = 1;
    while (b) {
        if (b & 1) {
            res = res * a % mod;
        }
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
void init(int n) {
    fac.resize(n + 1);
    inv.resize(n + 1);
    fac[0] = 1;
    for (int i = 1; i <= n; i++) {
        fac[i] = fac[i - 1] * i % mod;
    }
    inv[n] = qpow(fac[n], mod - 2);
    for (int i = n - 1; i >= 0; i--) {
        inv[i] = inv[i + 1] * (i + 1) % mod;
    }
}
// m中选n个
i64 C(i64 n, i64 m) {
    if (n > m || m < 0 || n < 0) {
        return 0;
    }
    return fac[m] * inv[m - n] % mod * inv[n] % mod;
}