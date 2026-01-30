#include <bits/stdc++.h>
using namespace std;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using f64 = long double;
using i128 = __int128_t;
using u128 = __uint128_t;

constexpr i64 mod = 998244353;

void FWT_OR(vector<i64> &A, int opt) {
    for (int i = 1; i < A.size(); i <<= 1) {
        for (int j = 0; j < A.size(); j += (i << 1)) {
            for (int k = 0; k < i; k++) {
                A[i + j + k] = (A[i + j + k] + opt * A[j + k] + mod) % mod;
            }
        }
    }
}

void FWT_AND(vector<i64> &A, int opt) {
    for (int i = 1; i < A.size(); i <<= 1) {
        for (int j = 0; j < A.size(); j += (i << 1)) {
            for (int k = 0; k < i; k++) {
                A[j + k] = (A[j + k] + opt * A[i + j + k] + mod) % mod;
            }
        }
    }
}

void FWT_XOR(vector<i64> &A, int opt) {
    static i64 inv2 = (mod + 1) / 2;
    for (int i = 1; i < A.size(); i <<= 1) {
        for (int j = 0; j < A.size(); j += (i << 1)) {
            for (int k = 0; k < i; k++) {
                i64 x = A[j + k], y = A[i + j + k];
                A[j + k] = (opt == 1 ? 1 : inv2) * (x + y) % mod;
                A[i + j + k] = (opt == 1 ? 1 : inv2) * (x - y + mod) % mod;
            }
        }
    }
}
template<typename Func>
vector<i64> multiply(vector<i64> A, vector<i64> B, Func dft) {
    dft(A, 1), dft(B, 1);
    for (int i = 0; i < A.size(); i++) {
        A[i] = A[i] * B[i] % mod;
    }
    dft(A, -1);
    return A;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<i64> a(1 << n), b(1 << n);
    for (int i = 0; i < (1 << n); ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < (1 << n); ++i) {
        cin >> b[i];
    }
    auto c = multiply(a, b, FWT_OR);
    auto d = multiply(a, b, FWT_AND);
    auto e = multiply(a, b, FWT_XOR);
    for (int i = 0; i < (1 << n); ++i) {
        cout << c[i] << " \n"[i + 1 == (1 << n)];
    }
    for (int i = 0; i < (1 << n); ++i) {
        cout << d[i] << " \n"[i + 1 == (1 << n)];
    }
    for (int i = 0; i < (1 << n); ++i) {
        cout << e[i] << " \n"[i + 1 == (1 << n)];
    }
    return 0;
}