#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128_t;

i64 exgcd(i64 a, i64 b, i64 &x, i64 &y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }
    i64 d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

// x === rem[i] (mod mode[i])
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
        ans = (ans + (__int128_t)rem[i] * m * x % M) % M;
    }
    return (ans + M) % M;
}

void solve() {
    i64 n;
    cin >> n;
    vector<i64> a(n + 1), b(n + 1);
    for (i64 i = 1; i <= n; i++) {
        cin >> a[i] >> b[i];
    }
    cout << CRT(a, b) << endl;
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