#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
// 线性基
struct LinearBasis {
    constexpr static int W = 60;
    array<i64, W + 1> a;
    void insert(i64 x) {
        for (int i = W; i >= 0; i--) {
            if (x >> i & 1) {
                if (a[i]) {
                    x ^= a[i];
                } else {
                    a[i] = x;
                    break;
                }
            }
        }
    }
    i64 query_max() {
        i64 res = 0;
        for (int i = W; i >= 0; i--) {
            res = max(res, res ^ a[i]);
        }
        return res;
    }
};
void solve() {
    i64 n;
    cin >> n;
    LinearBasis lb;
    for (i64 i = 1; i <= n; i++) {
        i64 x;
        cin >> x;
        lb.insert(x);
    }
    cout << lb.query_max() << "\n";



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