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

i64 inv(i64 a, i64 p) {
    i64 x, y;
    exgcd(a, p, x, y);
    return (x % p + p) % p;
}

i64 BSGS(i64 a, i64 b, i64 p) {
    a = a % p, b = b % p;
    if (1 % p == b % p)
        return 0;
    unordered_map<i64, i64> mp;
    i64 k = sqrtl(p) + 1;
    i64 res = 1;
    for (i64 i = 0; i <= k; i++) {
        mp[b * res % p] = i;
        res = res * a % p;
    }
    res = res * inv(a, p) % p;
    for (i64 i = 1, t = res; i <= k; i++) {
        if (mp.count(t))
            return i * k - mp[t];
        t = res * t % p;
    }
    return -1;
}

i64 EXBSGS(i64 a, i64 b, i64 p) {
    a = a % p, b = b % p;
    i64 d = __gcd(a, p), cnt = 0, y = 1;
    if (1 % p == b % p)
        return 0;
    while (d != 1) {
        if (b % d)
            return -1;
        p /= d, b /= d;
        y = a / d * y % p;
        d = __gcd(a, p);
        cnt++;
        if (b == y)
            return cnt;
    }
    i64 res = BSGS(a, b * inv(y, p), p);
    return res == -1 ? res : res + cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    i64 a, b, p;
    cin >> a >> p >> b;
    while (a && b && p) {
        i64 ans = EXBSGS(a, b, p);
        if (ans == -1)
            cout << "No Solution\n";
        else
            cout << ans << '\n';
        cin >> a >> p >> b;
    }
    return 0;
}