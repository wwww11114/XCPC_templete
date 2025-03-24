#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
typedef long double f64;
constexpr f64 eps = DBL_EPSILON;
vector<f64> Gauss(vector<vector<f64>> &a) {
    bool flag = 0;
    int n = a.size() - 1;
    vector<bool> free(n + 1);
    vector<f64> res(n + 1);
    for (int i = 1; i <= n; i++) {
        i64 p = i;
        for (int j = 1; j <= n; j++) {
            if (free[j]) {
                continue;
            }
            if (fabsl(a[j][i]) > fabsl(a[p][i])) {
                p = j;
            }
        }
        swap(a[i], a[p]);
        if (fabsl(a[i][i]) < eps) {
            flag = 1;
            continue;
        }
        free[i] = 1;
        for (int j = 1; j <= n; j++) {
            if (i == j) {
                continue;
            }
            f64 rat = a[j][i] / a[i][i];
            for (int k = 1; k <= n + 1; k++) {
                a[j][k] = a[j][k] - a[i][k] * rat;
            }
        }
    }
    if (flag) {
        for (int i = 1; i <= n; i++) {
            if (fabsl(a[i][i]) < eps && fabsl(a[i][n + 1]) > eps) {
                res[0] = -1;
                return res;
            }
        }
        res[0] = 1;
        return res;
    }
    for (int i = 1; i <= n; i++) {
        res[i] = a[i][n + 1] / a[i][i];
    }
    return res;
}

void solve() {
    i64 n;
    cin >> n;
    vector<vector<f64>> a(n + 1, vector<f64>(n + 2));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n + 1; j++) {
            cin >> a[i][j];
        }
    }
    vector<f64> res = Gauss(a);
    if (res[0] == -1) {
        cout << "-1\n";
        return;
    } else if (res[0] == 1) {
        cout << "0\n";
        return;
    }
    for (int i = 1; i <= n; i++) {
        cout << "x" << i << "=" << fixed << setprecision(3) << res[i] << '\n';
    }
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
