#include <bits/stdc++.h>
using namespace std;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using f64 = long double;
using i128 = __int128_t;
using u128 = __uint128_t;

// constexpr i64 mod = 1e9 + 7;
i64 mod;
i64 qpow(i64 a, i64 b) {
    i64 res = 1;
    while (b) {
        if (b & 1) {
            res = res * a % mod;
        }
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
i64 inv(i64 a) { return qpow(a, mod - 2); }

template<int n, int m>
struct Matrix : array<array<i64, m>, n>{
    using array<array<i64, m>, n>::array;
    friend Matrix operator+(const Matrix &x, const Matrix &y) {
        Matrix res{};
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                res[i][j] = (x[i][j] + y[i][j]) % mod;
            }
        }
        return res;
    }

    template<int p>
    friend Matrix<n, p> operator*(const Matrix &x, const Matrix<m, p> &y) {
        Matrix<n, p> res{};
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < p; j++) {
                for (int k = 0; k < m; k++) {
                    res[i][j] = (res[i][j] + x[i][k] * y[k][j]) % mod;
                }
            }
        }
        return res;
    }

    static Matrix<n, n> eye() {
        Matrix<n, n> res{};
        for (int i = 0; i < n; i++) {
            res[i][i] = 1;
        }
        return res;
    }

    static Matrix<n, n> qpow(Matrix<n, n> x, i64 y) {
        Matrix<n, n> res(eye());
        while (y) {
            if (y & 1) {
                res = res * x;
            }
            x = x * x;
            y >>= 1;
        }
        return res;
    }

    static i64 det(Matrix<n, n> x) {
        i64 res = 1;
        for (int i = 0; i < n; i++) {
            int pivot = i;
            for (int j = i; j < n; j++) {
                if (x[j][i]) {
                    pivot = j;
                    break;
                }
            }
            if (!x[pivot][i]) {
                return 0;
            }
            if (pivot != i) {
                swap(x[i], x[pivot]);
                res = (mod - res) % mod;
            }

            res = res * x[i][i] % mod;
            i64 invP = ::inv(x[i][i]);
            for (int j = i + 1; j < n; j++) {
                i64 delta = x[j][i] * invP % mod;
                for (int k = i; k < n; k++) {
                    x[j][k] = (x[j][k] - delta * x[i][k] % mod + mod) % mod;
                }
            }
        }
        return res;
    }

    static Matrix<m, n> T(const Matrix &x) {
        Matrix<m, n> res{};
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                res[j][i] = x[i][j];
            }
        }
        return res;
    }

    friend istream &operator>>(istream &is, Matrix &x) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                is >> x[i][j];
            }
        }
        return is;
    }

    friend ostream &operator<<(ostream &os, const Matrix &x) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                os << x[i][j] << " \n"[j + 1 == m];
            }
        }
        return os;
    }
};

int main() {
    int n;
    cin >> n >> mod;
    Matrix<2, 2> x;
    cin >> x;
    // auto [f, invx] = Matrix::inv(x);
    // if (f) {
    //     cout << invx << '\n';
    // } else {
    //     cout << "No Solution\n";
    // }
    cout << x << '\n';
    x = x * x;
    cout << x << '\n';
    return 0;
}