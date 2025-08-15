#include <bits/stdc++.h>
using namespace std;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using f64 = long double;
using i128 = __int128_t;
using u128 = __uint128_t;

void FFT(vector<complex<double>> &A, int opt = 1) {
    int n = A.size();
    vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        p[i] = p[i / 2] / 2 + (n / 2) * (i & 1);
    }
    for (int i = 0; i < n; ++i) {
        if (i < p[i]) {
            swap(A[i], A[p[i]]);
        }
    }
    for (int len = 2; len <= n; len <<= 1) {
        complex<double> w1 = {cos(2 * numbers::pi / len), sin(2 * numbers::pi / len) * opt};
        for (int i = 0; i < n; i += len) {
            complex<double> wk = {1, 0};
            for (int j = 0; j < len / 2; ++j) {
                complex<double> x = A[i + j];
                complex<double> y = A[i + j + len / 2] * wk;
                A[i + j] = x + y;
                A[i + j + len / 2] = x - y;
                wk *= w1;
            }
        }
    }
}


template<typename T>
vector<T> multiply(const vector<T> &A, const vector<T> &B) {
    int n = bit_ceil(A.size() + B.size() - 1);
    vector<complex<double>> v(n);
    for (int i = 0; i < A.size(); i++) {
        v[i].real(A[i]);
    }
    for (int i = 0; i < B.size(); i++) {
        v[i].imag(B[i]);
    }
    FFT(v);
    for (auto &x : v) {
        x *= x;
    }
    FFT(v, -1);
    std::vector<T> res(A.size() + B.size() - 1);
    for (int i = 0; i < res.size(); ++i) {
        res[i] = (T)round(v[i].imag() / 2 / n);
    }
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    std::vector<int> a(n + 1), b(m + 1);
    for (int i = 0; i <= n; ++i) {
        std::cin >> a[i];
    }
    for (int i = 0; i <= m; ++i) {
        std::cin >> b[i];
    }
    auto c = multiply(a, b);
    for (int i = 0; i < c.size(); ++i) {
        std::cout << c[i] << " \n"[i + 1 == c.size()];
    }
    return 0;
}