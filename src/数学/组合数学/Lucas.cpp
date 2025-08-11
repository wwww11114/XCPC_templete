#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
i64 qpow(i64 a, i64 b, i64 mod) {
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

struct Lucas {
    vector<i64> fac, inv;
    i64 mod;
    Lucas(i64 mod) : mod(mod) {
        fac.resize(mod);
        inv.resize(mod);
        fac[0] = 1;
        for (i64 i = 1; i < mod; i++) {
            fac[i] = fac[i - 1] * i % mod;
        }
        inv[mod - 1] = qpow(fac[mod - 1], mod - 2, mod);
        for (i64 i = mod - 2; i >= 0; i--) {
            inv[i] = inv[i + 1] * (i + 1) % mod;
        }
    }
    i64 C(i64 n, i64 m) {
        if (n == 0)
            return 1;
        i64 res = C(n / mod, m / mod);
        n %= mod;
        m %= mod;
        if (n > m || m < 0 || n < 0) {
            return 0;
        }
        res = res * fac[m] % mod * inv[m - n] % mod * inv[n] % mod;
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    i64 T;
    cin >> T;
    while (T--) {
        i64 n, m, p;
        cin >> n >> m >> p;
        Lucas lucas(p);
        cout << lucas.C(n, n + m) << '\n';
    }
    return 0;
}