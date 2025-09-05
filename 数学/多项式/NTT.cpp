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

void NTT(std::vector<i64> &A, int opt = 1) {
    int n = A.size();
    std::vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        p[i] = p[i / 2] / 2 + (n / 2) * (i & 1);
    }
    for (int i = 0; i < n; ++i) {
        if (i < p[i]) {
            std::swap(A[i], A[p[i]]);
        }
    }
    for (int len = 2; len <= n; len <<= 1) {
        i64 g1 = qpow(opt == 1 ? G : INVG, (mod - 1) / len);
        for (int i = 0; i < n; i += len) {
            i64 gk = 1;
            for (int j = 0; j < len / 2; ++j) {
                i64 x = A[i + j];
                i64 y = A[i + j + len / 2] * gk % mod;
                A[i + j] = (x + y) % mod;
                A[i + j + len / 2] = (x - y + mod) % mod;
                gk = (gk * g1) % mod;
            }
        }
    }
}

vector<i64> multiply(vector<i64> A, vector<i64> B) {
    auto m = A.size() + B.size() - 1;
    int n = bit_ceil(m);
    A.resize(n), B.resize(n);
    NTT(A), NTT(B);
    for (int i = 0; i < n; ++i) {
        A[i] = A[i] * B[i] % mod;
    }
    NTT(A, -1);
    A.resize(m);
    i64 invn = qpow(n, mod - 2);
    for (auto &x : A) {
        x = x * invn % mod;
    }
    return A;
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