#include <bits/stdc++.h>
using namespace std;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using f64 = long double;
using i128 = __int128_t;
using u128 = __uint128_t;

constexpr i64 mod = 998244353;

i64 qpow(i64 a, i64 b) {
    i64 res = 1;
    while (b) {
        if (b & 1) {
            res = res * a % mod;
        }
        b >>= 1;
        a = a * a % mod;
    }
    return res;
}

i64 inv(i64 a) {
    return qpow(a, mod - 2);
}

struct Lagrange {
    int n;
    vector<i64> y, fac, invfac;
    Lagrange() = default;
    Lagrange(const vector<i64> &_y) : n(_y.size() - 1), y(_y), fac(n + 1, 1), invfac(n + 1) {
        for (int i = 1; i <= n; i++) {
            fac[i] = fac[i - 1] * i % mod;
        }
        invfac[n] = inv(fac[n]);
        for (int i = n; i >= 1; i--) {
            invfac[i - 1] = invfac[i] * i % mod;
        }
    }
// 1 - n
    i64 solve(i64 k) {
        if (k <= n) {
            return y[k];
        }
        vector<i64> pre(n + 1, 1), suf(n + 2, 1);
        for (int i = 1; i <= n; i++) {
            pre[i] = pre[i - 1] * (k - i) % mod;
        }
        for (int i = n; i >= 0; i--) {
            suf[i] = suf[i + 1] * (k - i) % mod;
        }
        i64 ans = 0;
        for (int i = 1; i <= n; i++) {
            ans = (ans + y[i] * pre[i - 1] % mod * suf[i + 1] % mod * invfac[i - 1] % mod * invfac[n - i] % mod * (n - i & 1 ? mod - 1 : 1)) % mod;
        }
        return ans;
    }
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int n;
    i64 k;
    cin >> n >> k;
    vector<i64> y(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> y[i] >> y[i];
    }
    Lagrange la(y);
    cout << la.solve(k) << '\n';
    return 0;
}