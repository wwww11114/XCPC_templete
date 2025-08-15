#include <bits/stdc++.h>
using namespace std;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using f64 = long double;
using i128 = __int128_t;
using u128 = __uint128_t;

constexpr i64 mod = 998244353;
constexpr i64 G = 3;
constexpr i64 INVG = 332748118;

i64 qpow(i64 a, i64 b) {
    i64 res = 1;
    while (b) {
        if (b & 1) {
            res = res * a % mod;
        }
        b >>= 1;
        a = a * a % mod;
    }
    return res;
}

i64 inv(i64 a) {
    return qpow(a, mod - 2);
}

void FWT_OR(std::vector<i64> &A, int opt = 1) {
    int n = A.size();
    for (int i = 1; i < (1 << n); i *= 2) {
        for (int j = 0; j < (1 << n); j += 2 * i) {
            for (int k = 0; k < i; k++) {
                A[i + j + k] = (A[i + j + k] + opt * A[j + k] + mod) % mod;
            }
        }
    }
}

void FWT_AND(std::vector<i64> &A, int opt = 1) {
    int n = A.size();
    for (int i = 1; i < (1 << n); i *= 2) {
        for (int j = 0; j < (1 << n); j += 2 * i) {
            for (int k = 0; k < i; k++) {
                A[j + k] = (A[j + k] + opt * A[i + j + k] + mod) % mod;
            }
        }
    }
}

void FWT_XOR(std::vector<i64> &A, int opt = 1) {
    int n = A.size();
    static i64 inv2 = inv(2);
    for (int i = 1; i < n; i <<= 1) {
        for (int j = 0; j < n; j += 2 * i) {
            for (int k = 0; k < i; k++) {
                i64 x = A[j + k], y = A[i + j + k];
                A[j + k] = (opt == 1 ? 1 : inv2) * (x + y) % mod;
                A[i + j + k] = (opt == 1 ? 1 : inv2) * (x - y + mod) % mod;
            }
        }
    }
}


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<i64> a(n + 1);
    for (int i = 0; i <= n; ++i) {
        std::cin >> a[i];
    }
    return 0;
}