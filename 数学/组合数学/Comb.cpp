#include <bits/stdc++.h>
using namespace std;
typedef long long i64;

constexpr int mod = 1e9 + 7;

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
i64 inv(i64 a) { return qpow(a, mod - 2); }
struct Comb {
    vector<i64> _fac, _invfac;
    int n;
    Comb() : n(0), _fac(1, 1), _invfac(1, 1) {}
    Comb(int n) : Comb() { init(n); }
    void init(int m) {
        if (m <= n) return;
        _fac.resize(m + 1);
        _invfac.resize(m + 1);
        for (int i = n + 1; i <= m; i++) {
            _fac[i] = _fac[i - 1] * i % mod;
        }
        _invfac[m] = inv(_fac[m]);
        for (int i = m; i > n; i--) {
            _invfac[i - 1] = _invfac[i] * i % mod;
        }
        n = m;
    }
    i64 fac(int m) {
        if (m > n) init(2 * m);
        return _fac[m];
    }
    i64 invfac(int m) {
        if (m > n) init(2 * m);
        return _invfac[m];
    }
    i64 operator()(int n, int m) {
        if (m < 0 || n < 0 || n < m) {
            return 0;
        }
        return fac(n) * invfac(m) % mod * invfac(n - m) % mod;
    }
} comb;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int n, k, m;
    cin >> n >> k >> m;
    cout << comb(n, k) * qpow(m, k) % mod << '\n';
    return 0;
}