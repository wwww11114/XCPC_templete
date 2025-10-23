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

i64 Lagrange(const vector<pair<i64, i64>> &points, i64 k) {
    i64 ans = 0;
    for (int i = 0; i < points.size(); i++) {
        auto [x, y] = points[i];
        i64 sum = 1;
        for (int j = 0; j < points.size(); j++) {
            if (i == j) {
                continue;
            }
            auto [nx, _] = points[j];
            y = y * (k - nx + mod) % mod;
            sum = sum * (x - nx + mod) % mod;
        }
        ans = (ans + y * inv(sum)) % mod;
    }
    return ans;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int n;
    i64 k;
    cin >> n >> k;
    vector<pair<i64, i64>> v(n);
    for (auto &[x, y] : v) {
        cin >> x >> y;
    }
    cout << Lagrange(v, k) << '\n';
    return 0;
}