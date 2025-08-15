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

struct Poly {
    std::vector<i64> v;

    Poly() = default;
    explicit Poly(const i64 &_v) : v(1, _v) {}
    explicit Poly(const vector<i64> &_v) : v(_v.begin(), _v.end()) {}

    int size() const { return v.size(); }

    i64 operator[](int idx) const {
        if (idx < 0 || idx >= size()) {
            return 0;
        }
        return v[idx];
    }

    friend Poly operator+(const Poly &x, const Poly &y) {
        vector<i64> res(max(x.size(), y.size()));
        for (int i = 0; i < res.size(); i++) {
            res[i] = (x[i] + y[i]) % mod;
        }
        return Poly(res);
    }
    friend Poly operator-(const Poly &x, const Poly &y) {
        vector<i64> res(max(x.size(), y.size()));
        for (int i = 0; i < res.size(); i++) {
            res[i] = (x[i] - y[i] + mod) % mod;
        }
        return Poly(res);
    }
    friend Poly operator*(const Poly &x, const Poly &y) {
        return Poly(multiply(x.v, y.v));
    }
    friend Poly operator/(const Poly &x, const Poly &y) {
        int n = x.size() - y.size() + 1;
        return rev(modxk(rev(x) * inv(rev(y), n), n));
    }

    friend Poly operator+(const Poly &x, const i64 &y) {
        vector<i64> res(x.size());
        for (int i = 0; i < res.size(); i++) {
            res[i] = (x[i] + y) % mod;
        }
        return Poly(res);
    }
    friend Poly operator-(const Poly &x, const i64 &y) {
        vector<i64> res(x.size());
        for (int i = 0; i < res.size(); i++) {
            res[i] = (x[i] - y + mod) % mod;
        }
        return Poly(res);
    }
    friend Poly operator*(const Poly &x, const i64 &y) {
        vector<i64> res(x.size());
        for (int i = 0; i < res.size(); i++) {
            res[i] = x[i] * y % mod;
        }
        return Poly(res);
    }
    friend Poly operator/(const Poly &x, const i64 &y) {
        return x * ::inv(y);
    }

    static Poly inv(const Poly &x) {
        return inv(x, x.size());
    }
    static Poly inv(const Poly &x, int n) {
        assert(x[0]);
        Poly b(::inv(x[0]));
        int k = 1;
        while (k < n) {
            k *= 2;
            b = modxk(b * (Poly(2) - modxk(x, k) * b), k);
        }
        return modxk(b, n);
    }
    
    static Poly qpow(const Poly &a, i64 b) {
        return qpow(a, b, a.size());
    }
    static Poly qpow(const Poly &a, i64 b, int n) {
        return exp(ln(a, n) * b, n);
    }

    static Poly sqrt(const Poly &x) {
        return sqrt(x, x.size());
    }
    static Poly sqrt(const Poly &x, int n) {
        Poly y(1);
        int k = 1;
        while (k < n) {
            k *= 2;
            y = (y + modxk(modxk(x, k) * inv(y, k), k)) * ((mod + 1) / 2);
        }
        return modxk(y, n);
    }

    static Poly ln(const Poly &x) {
        return ln(x, x.size());
    }
    static Poly ln(const Poly &x, int n) {
        return modxk(integr(deriv(x) * inv(x, n)), n);
    }

    static Poly exp(const Poly &x) {
        return exp(x, x.size());
    }
    static Poly exp(const Poly &x, int n) {
        Poly y(1);
        int k = 1;
        while (k < n) {
            k *= 2;
            y = modxk(y * (Poly(1) - ln(y, k) + modxk(x, k)), k);
        }
        return modxk(y, n);
    }
    // 求导 
    static Poly deriv(const Poly &x) {
        if (!x.size()) {
            return Poly();
        }
        std::vector<i64> res(x.size() - 1);
        for (int i = 0; i < x.size() - 1; i++) {
            res[i] = (i + 1) * x[i + 1] % mod;
        }
        return Poly(res);
    }
    // 积分
    static Poly integr(const Poly &x) {
        if (!x.size()) {
            return Poly();
        }
        std::vector<i64> res(x.size() + 1);
        for (int i = 0; i < x.size(); i++) {
            res[i + 1] = x[i] * ::inv(i + 1) % mod;
        }
        return Poly(res);
    }

    static Poly mulxk(Poly x, int k) {
        x.v.insert(x.v.begin(), k, 0);
        return x;
    }
    static Poly modxk(Poly x, int k) {
        x.v.resize(min(k, x.size()));
        return x;
    }
    static Poly divxk(Poly x, int k) {
        if (x.size() <= k) {
            return Poly();
        }
        x.v.erase(x.v.begin(), x.v.begin() + k);
        return x;
    }
    static Poly rev(Poly x) {
        reverse(x.v.begin(), x.v.end());
        return Poly(x);
    }

    static vector<i64> multiply(const vector<i64> &A, const vector<i64> &B) {
        int n = bit_ceil(A.size() + B.size() - 1);
        vector<i64> va(A.begin(), A.end());
        vector<i64> vb(B.begin(), B.end());
        va.resize(n), vb.resize(n);
        NTT(va), NTT(vb);
        for (int i = 0; i < n; ++i) {
            va[i] = va[i] * vb[i] % mod;
        }
        NTT(va, -1);
        i64 invn = ::inv(n);
        va.resize(A.size() + B.size() - 1);
        for (auto &x : va) {
            x = x * invn % mod;
        }
        return va;
    }

    static void NTT(vector<i64> &A, int opt = 1) {
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
            i64 g1 = ::qpow(opt == 1 ? G : INVG, (mod - 1) / len);
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
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int n;
    std::cin >> n;
    string s;
    cin >> s;
    i64 k = 0;
    for (int i = 0; i < s.size(); i++) {
        k = (k * 10 + s[i] - '0') % mod;
    }
    vector<i64> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    auto q = Poly::qpow(Poly(a), k);
    for (int i = 0; i < q.size(); ++i) {
        std::cout << q[i] << " \n"[i + 1 == q.size()];
    }
    return 0;
}