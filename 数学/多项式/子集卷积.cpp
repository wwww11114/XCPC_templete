#include <bits/stdc++.h>
using namespace std;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using f64 = long double;
using i128 = __int128_t;
using u128 = __uint128_t;

constexpr i64 mod = 1e9 + 9;

void FWT_OR(std::vector<i64> &A, int opt) {
    for (int i = 1; i < A.size(); i *= 2) {
        for (int j = 0; j < A.size(); j += 2 * i) {
            for (int k = 0; k < i; k++) {
                A[i + j + k] = (A[i + j + k] + opt * A[j + k] + mod) % mod;
            }
        }
    }
}

vector<i64> SubSetmultiply(const vector<i64> &A, const vector<i64> &B) {
    int m = bit_width(A.size());
    int n = A.size();
    vector a(m + 1, vector<i64>(n));
    vector b(m + 1, vector<i64>(n));
    vector res(m + 1, vector<i64>(n));
    for (int i = 0; i < n; i++) {
        a[popcount<u32>(i)][i] = A[i];
    }
    for (int i = 0; i < n; i++) {
        b[popcount<u32>(i)][i] = B[i];
    }
    for (int i = 0; i <= m; i++) {
        FWT_OR(a[i], 1);
        FWT_OR(b[i], 1);
    }
    for (int i = 0; i <= m; i++) {
        for (int j = 0; i + j <= m; j++) {
            for (int k = 0; k < n; k++) {
                res[i + j][k] = (res[i + j][k] + a[i][k] * b[j][k]) % mod;
            }
        }
    }
    for (int i = 0; i <= m; i++) {
        FWT_OR(res[i], -1);
    }
    vector<i64> ans(n);
    for (int i = 0; i < n; i++) {
        ans[i] = res[popcount<u32>(i)][i];
    }
    return ans;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int n;
    cin >> n;
    vector<i64> a(1 << n);
    vector<i64> b(1 << n);
    for (int i = 0; i < (1 << n); i++) {
        cin >> a[i];
    }
    for (int i = 0; i < (1 << n); i++) {
        cin >> b[i];
    }
    auto res = SubSetmultiply(a, b);
    for (int i = 0; i < (1 << n); i++) {
        cout << res[i] << " \n"[i + 1 == (1 << n)];
    }
    return 0;
}