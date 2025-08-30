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

struct Matrix {
    int n, m;
    vector<vector<i64>> v;

    Matrix() : n(0), m(0) {}
    explicit Matrix(int _n) : n(_n), m(_n), v(_n, vector<i64>(_n)) {}
    explicit Matrix(int _n, int _m) : n(_n), m(_m), v(_n, vector<i64>(_m)) {}
    explicit Matrix(const vector<vector<i64>> &_v) : n(_v.size()), m(_v[0].size()), v(_v) {}

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
            for (int j = 0; j < x.m; j++) {
                for (int k = 0; k < y.m; k++) {
                    res[i][k] = (res[i][k] + x[i][j] * y[j][k]) % mod;
                }
            }
        }
        return res;
    }

    void resize(int _n, int _m) {
        n = _n, m = _m;
        v.resize(n);
        for (auto &x : v) {
            x.resize(m);
        }
    }

    bool Gauss() {
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                if (v[j][i]) {
                    swap(v[i], v[j]);
                    break;
                }
            }
            if (!v[i][i]) {
                return false;
            }
            i64 invP = ::inv(v[i][i]);
            for (int j = 0; j < n; j++) {
                if (i == j) {
                    continue;
                }
                i64 delat = v[j][i] * invP % mod;
                for (int k = 0; k < m; k++) {
                    v[j][k] = (v[j][k] - delat * v[i][k] % mod + mod) % mod;
                }
            }
        }
        return true;
    }

    static tuple<bool, Matrix> inv(Matrix x) {
        assert(x.n == x.m);
        x.resize(x.n, x.m * 2);
        for (int i = 0; i < x.n; i++) {
            x[i][x.n + i] = 1;
        }
        if (!x.Gauss()) {
            return {false, Matrix()};
        }
        Matrix res(x.n);
        for (int i = 0; i < x.n; i++) {
            i64 invP = ::inv(x[i][i]);
            for (int j = 0; j < x.n; j++) {
                res[i][j] = x[i][j + x.n] * invP % mod;
            }
        }
        return {true, res};
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

    static i64 det(Matrix x) {
        assert(x.n == x.m);
        x.Gauss();
        i64 res = 1;
        for (int i = 0; i < x.n; i++) {
            res = res * x[i][i] % mod;
        }
        return res;
    }

    static Matrix T(const Matrix &x) {
        Matrix res(x.m, x.n);
        for (int i = 0; i < x.n; i++) {
            for (int j = 0; j < x.m; j++) {
                res[j][i] = x[i][j];
            }
        }
        return res;
    }

    friend istream &operator>>(istream &is, Matrix &x) {
        for (int i = 0; i < x.n; i++) {
            for (int j = 0; j < x.m; j++) {
                is >> x[i][j];
            }
        }
        return is;
    }

    friend ostream &operator<<(ostream &os, const Matrix &x) {
        for (int i = 0; i < x.n; i++) {
            for (int j = 0; j < x.m; j++) {
                os << x[i][j] << " \n"[j + 1 == x.m];
            }
        }
        return os;
    }
};

int main() {
    int n;
    cin >> n >> mod;
    Matrix x(n);
    cin >> x;
    // auto [f, invx] = Matrix::inv(x);
    // if (f) {
    //     cout << invx << '\n';
    // } else {
    //     cout << "No Solution\n";
    // }
    cout << Matrix::det(x) << '\n';
    return 0;
}