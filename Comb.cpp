#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
const int N = 1e5 + 10;
const int mod = 1e9 + 7;
i64 fac[N], ifac[N];
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
void init() {
    fac[0] = 1;
    for (int i = 1; i < N; i++) {
        fac[i] = fac[i - 1] * i % mod;
    }
    ifac[N - 1] = qpow(fac[N - 1], mod - 2);
    for (int i = N - 2; i >= 0; i--) {
        ifac[i] = ifac[i + 1] * (i + 1) % mod;
    }
}
// m中选n个
i64 C(i64 n, i64 m) {
    if (n > m || m < 0 || n < 0) {
        return 0;
    }
    return fac[m] * ifac[m - n] % mod * ifac[n] % mod;
}