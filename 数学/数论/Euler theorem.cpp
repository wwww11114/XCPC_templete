#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
i64 get_phi(i64 n) {
    i64 res = n;
    for (i64 i = 2; i <= n / i; i++) {
        if (n % i == 0) {
            res = res / i * (i - 1);
            while (n % i == 0) {
                n /= i;
            }
        }
    }
    if (n > 1) {
        res = res / n * (n - 1);
    }
    return res;
}
i64 qpow(i64 a, i64 b, i64 mod) {
    i64 res = 1;
    while (b) {
        if (b & 1)
            res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
i64 EXET(i64 a, string s, i64 p) {
    i64 phi = get_phi(p), b = 0, flag = 0;
    for (i64 i = 0; i < s.size(); i++) {
        b = b * 10 + s[i] - '0';
        if (b >= phi) {
            b %= phi;
            flag = 1;
        }
    }
    if (gcd(a, p) != 1 && flag) {
        b += phi;
    }
    return qpow(a, b, p);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    i64 a, p;
    string b;
    cin >> a >> p >> b;
    cout << EXET(a, b, p) << '\n';
    return 0;
}