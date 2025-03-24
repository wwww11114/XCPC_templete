#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
i64 randint(i64 l, i64 r) { return uniform_int_distribution<i64>(l, r)(rnd); }
i64 randlong(i64 l, i64 r) { return uniform_int_distribution<i64>(l, r)(rnd); }
double randreal(double l, double r) { return uniform_real_distribution<double>(l, r)(rnd); }
void solve() {
    cout << randint(1, 100) << '\n';
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