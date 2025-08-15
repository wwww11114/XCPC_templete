#include <bits/stdc++.h>
using namespace std;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using f64 = long double;
using i128 = __int128_t;
using u128 = __uint128_t;

constexpr i64 mod = 1e9 + 7;

template<int n, int m>
struct Matrix {
    vector<vector<i64>> v;

    Matrix() = default;
    // Matrix(int _n) : n(_n), m(_n), v(_n, vector<i64>(_n)) {}
    // Matrix(int _n, int _m) : n(_n), m(_m), v(_n, vector<i64>(_m)) {}
    // Matrix(const vector<vector<i64>> &_v) : n(_v.size()), m(_v[0].size()), v(_v) {}

    vector<i64> &operator[](int x) {
        return v[x];
    }

    const vector<i64> &operator[](int x) const {
        return v[x];
    }

    friend Matrix operator+(const Matrix &x, const Matrix &y) {
        assert(x.n == y.n && x.m == y.m);
        Matrix res(x.n, x.m);
        for (int i = 0; i < x.n; i++) {
            for (int j = 0; j < x.m; j++) {
                res[i][j] = (x[i][j] + y[i][j]) % mod;
            }
        }
        return res;
    }

    friend Matrix operator*(const Matrix &x, const Matrix &y) {
        assert(x.m == y.n);
        Matrix res(x.n, y.m);
        for (int i = 0; i < x.n; i++) {
            for (int j = 0; j < y.m; j++) {
                for (int k = 0; k < x.m; k++) {
                    res[i][j] = (res[i][j] + x[i][k] * y[k][j]) % mod;
                }
            }
        }
        return res;
    }

    static Matrix eye(int n) {
        Matrix res(n);
        for (int i = 0; i < n; i++) {
            res[i][i] = 1;
        }
        return res;
    }

    static Matrix qpow(Matrix x, i64 y) {
        Matrix res(eye(x.n));
        while (y) {
            if (y & 1) {
                res = res * x;
            }
            x = x * x;
            y >>= 1;
        }
        return res;
    }
};



int main() {
    int n;
    i64 k;
    cin >> n >> k;
    Matrix<100, 100> x(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> x[i][j];
        }
    }
    x = Matrix<100, 100>::qpow(x, k);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << x[i][j] << " \n"[j + 1 == n];
        }
    }
    return 0;
}