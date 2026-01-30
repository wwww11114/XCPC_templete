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

struct Poly : vector<i64> {
    using vector<i64>::vector;
    inline static vector<i64> w{1};

    friend Poly operator+(Poly res, const i64 &y) {
        for (auto &x : res) {
            x = x + y >= mod ? x + y - mod : x + y;
        }
        return res;
    }
    friend Poly operator-(const Poly &x, const i64 &y) {
        return x + (mod - y);
    }
    friend Poly operator*(Poly res, const i64 &y) {
        for (auto &x : res) {
            x = x * y % mod;
        }
        return res;
    }
    friend Poly operator/(const Poly &x, const i64 &y) {
        return x * ::inv(y);
    }
    friend Poly operator%(Poly res, size_t k) {
        res.resize(min(res.size(), k));
        return res;
    }
    static Poly mulxk(Poly x, int k) {
        x.insert(x.begin(), k, 0);
        return x;
    }
    static Poly divxk(Poly x, int k) {
        if ((int)x.size() <= k) {
            return Poly();
        }
        x.erase(x.begin(), x.begin() + k);
        return x;
    }

    friend Poly operator+(Poly res, const Poly &y) {
        res.resize(max(res.size(), y.size()));
        for (int i = 0; i < (int)y.size(); i++) {
            res[i] = res[i] + y[i] >= mod ? res[i] + y[i] - mod : res[i] + y[i];
        }
        return res;
    }
    friend Poly operator-(const Poly &x, const Poly &y) {
        return x + y * (mod - 1);
    }
    friend Poly operator*(Poly x, Poly y) {
        auto m = x.size() + y.size() - 1;
        int n = bit_ceil(m);
        x.resize(n), y.resize(n);
        NTT(x), NTT(y);
        for (int i = 0; i < n; i++) {
            x[i] = x[i] * y[i] % mod;
        }
        NTT(x, -1);
        x.resize(m);
        x = x * ::inv(n);
        return x;
    }
    friend Poly operator/(const Poly &x, const Poly &y) {
        int n = x.size() - y.size() + 1;
        return rev(rev(x) * inv(rev(y), n) % n);
    }

    static Poly inv(const Poly &x) {
        return inv(x, x.size());
    }
    static Poly inv(const Poly &x, int n) {
        assert(x[0]);
        Poly res{::inv(x[0])};
        for (int k = 2; k < 2 * n; k *= 2) {
            res = res * (Poly{2} - x % k * res) % k;
        }
        return res % n;
    }

    static Poly qpow(const Poly &a, i64 b) {
        return qpow(a, b, a.size());
    }
    static Poly qpow(const Poly &a, i64 b, int n) {
        assert(a[0] == 1);
        return exp(ln(a, n) * b, n);
    }

    static Poly pow(const Poly &a, i64 b) {
        return pow(a, b, a.size());
    }
    static Poly pow(const Poly &a, i64 b, int n) {
        int id = 0;
        while (id < (int)a.size() && !a[id]) {
            id++;
        }
        if (id * b >= n) {
            return Poly(n);
        }
        Poly res = divxk(a, id) / a[id];
        return mulxk(exp(ln(res, n - id * b) * b, n - id * b) * ::qpow(a[id], b), id * b);
    }

    static Poly sqrt(const Poly &x) {
        return sqrt(x, x.size());
    }
    static Poly sqrt(const Poly &x, int n) {
        Poly res{1};
        for (int k = 2; k < 2 * n; k *= 2) {
            res = (res + x % k * inv(res, k) % k) * ((mod + 1) / 2);
        }
        return res % n;
    }

    static Poly ln(const Poly &x) {
        return ln(x, x.size());
    }
    static Poly ln(const Poly &x, int n) {
        return integr(deriv(x) * inv(x, n) % n) % n;
    }

    static Poly exp(const Poly &x) {
        return exp(x, x.size());
    }
    static Poly exp(const Poly &x, int n) {
        Poly res{1};
        for (int k = 2; k < 2 * n; k *= 2) {
            res = res * (Poly{1} - ln(res, k) + x % k) % k;
        }
        return res % n;
    }

    static Poly sin(const Poly &x) {
        return sin(x, x.size());
    }
    static Poly sin(const Poly &x, int n) {
        static i64 i = 86583718;
        return (exp(x * i, n) - exp(x * (mod - i), n)) * ::inv(2 * i) % n;
    }

    static Poly cos(const Poly &x) {
        return cos(x, x.size());
    }
    static Poly cos(const Poly &x, int n) {
        static i64 i = 86583718;
        return (exp(x * i, n) + exp(x * (mod - i), n)) * ((mod + 1) / 2);
    }

    static Poly tan(const Poly &x) {
        return tan(x, x.size());
    }
    static Poly tan(const Poly &x, int n) {
        static i64 i = 86583718;
        Poly a = exp(x * i, n);
        Poly b = exp(x * (mod - i), n);
        return (a - b) * ::inv(2 * i) * inv((a + b) * ((mod + 1) / 2), n) % n;
    }

    static Poly arcsin(const Poly &x) {
        return arcsin(x, x.size());
    }
    static Poly arcsin(const Poly &x, int n) {
        return integr(deriv(x) * inv(sqrt(Poly{1} - x * x % n, n), n) % n) % n;
    }

    static Poly arccos(const Poly &x) {
        return arccos(x, x.size());
    }
    static Poly arccos(const Poly &x, int n) {
        return Poly{0} - arcsin(x, n);
    }

    static Poly arctan(const Poly &x) {
        return arctan(x, x.size());
    }
    static Poly arctan(const Poly &x, int n) {
        return integr(deriv(x) * inv(Poly{1} + x * x % n, n) % n) % n;
    }

    static Poly deriv(const Poly &x) {
        if (x.empty()) {
            return Poly();
        }
        Poly res(x.size() - 1);
        for (int i = 0; i < (int)x.size() - 1; i++) {
            res[i] = (i + 1) * x[i + 1] % mod;
        }
        return res;
    }

    static Poly integr(const Poly &x) {
        static vector<i64> inv{1, 1};
        int m = inv.size();
        int n = x.size();
        if (m <= n) {
            inv.resize(2 * n);
            for (int i = m; i < 2 * n; i++) {
                inv[i] = (mod - mod / i) * inv[mod % i] % mod;
            }
        }
        Poly res(n + 1);
        for (int i = 0; i < n; i++) {
            res[i + 1] = x[i] * inv[i + 1] % mod;
        }
        return res;
    }

    static Poly rev(Poly x) {
        ranges::reverse(x);
        return x;
    }

    static void NTT(vector<i64> &A, int opt = 1) {
        int n = A.size();
        init(n);
        for (int i = 0, j = 0; i < n; i++) {
            if (i > j) {
                std::swap(A[i], A[j]);
            }
            for (int k = n >> 1; (j ^= k) < k; k >>= 1);
        }
        for (int i = 1; i < n; i <<= 1) {
            for (int j = 0; j < n; j += (i << 1)) {
                for (int k = j; k < i + j; k++) {
                    int t = w[k + i - j] * A[i + k] % mod;
                    A[k + i] = (A[k] - t < 0 ? A[k] - t + mod : A[k] - t);
                    A[k] = (A[k] + t >= mod ? A[k] + t - mod : A[k] + t);
                }
            }
        }
        if (opt == -1) {
            reverse(A.begin() + 1, A.end());
        }
    }
    static void init(int n) {
        int m = w.size();
        if (n <= m) return;
        w.resize(n);
        i64 wn = ::qpow(G, (mod - 1) / n);
        w[n >> 1] = 1;
        for (int i = (n >> 1) + 1; i < n; i++) {
            w[i] = w[i - 1] * wn % mod;
        }
        for (int i = n - 1; i >= m; i--) {
            w[i >> 1] = w[i];
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int n;
    cin >> n;
    Poly F(n);
    for (int i = 1; i < n; i++) {
        cin >> F[i];
    }
    F = Poly::inv(Poly{1} - F);
    for (int i = 0; i < n; i++) {
        cout << F[i] << " \n"[i + 1 == n];
    }
    return 0;
}