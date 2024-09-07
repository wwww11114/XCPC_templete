#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
i64 exgcd(i64 a, i64 b, i64 &x, i64 &y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }
    i64 d = exgcd(b, a % b, x, y);
    i64 t = x;
    x = y;
    y = t - a / b * y;
    return d;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    return 0;
}