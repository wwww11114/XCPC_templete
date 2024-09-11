#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
i64 exgcd(i64 a, i64 b, i64 &x, i64 &y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }
    i64 d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}
i64 CRT(vector<i64> &mode, vector<i64> &rem) {
    i64 M = 1, n = mode.size() - 1;
    for (i64 i = 1; i <= n; i++) {
        M *= mode[i];
    }
    i64 ans = M;
    for (i64 i = 1; i <= n; i++) {
        i64 m = M / mode[i];
        i64 x, y;
        exgcd(m, mode[i], x, y);
        ans += (__int128_t)rem[i] * m * x % M;
        ans %= M;
    }
    return (ans + M) % M;
}
i64 EXCRT(vector<i64> &mode, vector<i64> &rem) {
    i64 M = mode[1], R = rem[1], n = mode.size() - 1, ans = 0;
    for (i64 i = 2; i <= n; i++) {
        i64 gd = __gcd(M, mode[i]);
        i64 lm = M / gd * mode[i];
        if ((rem[i] - R) % gd)
            return -1;
        i64 x, y;
        exgcd(M / gd, mode[i] / gd, x, y);
        R = (R + (__int128_t)(rem[i] - R) / gd * x * M % lm + lm) % lm;
        M = lm;
    }
    return R;
}
void solve() {
    i64 n;
    cin >> n;
    vector<i64> a(n + 1), b(n + 1);
    for (i64 i = 1; i <= n; i++) {
        cin >> a[i] >> b[i];
    }
    cout << EXCRT(a, b) << endl;
    return;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    i64 T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}