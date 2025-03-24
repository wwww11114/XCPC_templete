#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
template <class T>
constexpr T qpow(T a, i64 b, T res = 1ll) {
    for (; b != 0; b /= 2, a *= a) {
        if (b & 1) {
            res *= a;
        }
    }
    return res;
}

namespace Dirichlet {
    constexpr int N = 10;
    vector<int> pirme;
    array<bool, N> not_prime{};
    // 积性函数
    template <typename T>
    struct mul_func {
        vector<T> f;
        int n;
        mul_func(int n = N) : n(n), f(n + 1) {}
        T &operator[](int x) {
            return f[x];
        }
        const T &operator[](int x) const {
            return f[x];
        }
        // Dirichlet卷积
        mul_func operator*(const mul_func &rhs) const {
            mul_func res(n);
            for (int i = 1; i <= n; i++) {
                for (int j = i; j <= n; j += i) {
                    res[j] += f[i] * rhs[j / i];
                }
            }
            return res;
        }
        mul_func &operator*=(const mul_func &rhs) {
            return *this = *this * rhs;
        }
        mul_func operator*(const T &k) {
            mul_func res(n);
            for (int i = 1; i <= n; i++) {
                res[i] = f[i] * k;
            }
            return res;
        }
        mul_func &operator*=(const T &k) {
            return *this = *this * rhs;
        }
        mul_func operator+(const mul_func &rhs) {
            mul_func res(n);
            for (int i = 1; i <= n; i++) {
                res[i] = f[i] + rhs[i];
            }
            return res;
        }
        friend istream &operator<<(istream &os, const mul_func &a) {
            for (int i = 1; i <= a.n; i++) {
                os >> a[i];
            }
            return os;
        }
        friend ostream &operator<<(ostream &os, const mul_func &a) {
            for (int i = 1; i <= a.n; i++) {
                os << a[i] << " \n"[i == a.n];
            }
            return os;
        }
    };
    void init(int n = N) {
        not_prime[1] = true;
        for (i64 i = 2; i <= n; i++) {
            if (!not_prime[i]) {
                pirme.push_back(i);
            }
            for (i64 j : pirme) {
                if (i * j > n) {
                    break;
                }
                not_prime[i * j] = true;
                if (i % j == 0) {
                    break;
                }
            }
        }
    }
    // 欧拉函数
    mul_func<int> phi(int n = N) {
        mul_func<int> phi(n);
        phi[1] = 1;
        for (int i = 2; i <= n; i++) {
            if (!not_prime[i]) {
                phi[i] = i - 1;
            }
            for (int j : pirme) {
                if (i * j > n) {
                    break;
                }
                if (i % j == 0) {
                    phi[i * j] = phi[i] * j;
                    break;
                }
                phi[i * j] = phi[i] * phi[j];
            }
        }
        return phi;
    }
    // 莫比乌斯函数
    mul_func<int> mobius(int n = N) {
        mul_func<int> mu(n);
        mu[1] = 1;
        for (int i = 2; i <= n; i++) {
            if (!not_prime[i]) {
                mu[i] = -1;
            }
            for (int j : pirme) {
                if (i * j > n || i % j == 0) {
                    break;
                }
                mu[i * j] = -mu[i];
            }
        }
        return mu;
    }
    // 约数个数
    mul_func<int> divisor(int n = N) {
        mul_func<int> d(n);
        d[1] = 1;
        for (int i = 1; i <= n; i++) {
            if (!not_prime[i]) {
                d[i] = 2;
            }
            for (int j : pirme) {
                if (i * j > n) {
                    break;
                }
                if (i % j == 0) {
                    d[i * j] = d[i] / (d[i / j] + 1) * (d[i / j] + 2);
                    break;
                }
                d[i * j] = d[i] * d[j];
            }
        }
        return d;
    }
    // 约数和
    mul_func<i64> div_sum(int n = N) {
        mul_func<i64> ds(n);
        vector<int> low(n + 1); // 维护每个数的最小质因数的最高幂次
        ds[1] = 1;
        for (int i = 2; i <= n; i++) {
            if (!not_prime[i]) {
                ds[i] = i + 1;
                low[i] = i;
            }
            for (int j : pirme) {
                if (i * j > n) {
                    break;
                }
                if (i % j == 0) {
                    low[i * j] = low[i] * j;
                    ds[i * j] = ds[i] * j + ds[i / low[i]];
                    break;
                }
                low[i * j] = low[j];
                ds[i * j] = ds[i] * ds[j];
            }
        }
        return ds;
    }
    // 单位函数 
    mul_func<int> unit(int n = N) {
        mul_func<int> u(n);
        for (int i = 1; i <= n; i++) {
            u[i] = 1;
        }
        return u;
    }
    // 恒等函数
    mul_func<int> Id(int n = N) {
        mul_func<int> id(n);
        for (int i = 1; i <= n; i++) {
            id[i] = i;
        }
        return id;
    }
    // 幂函数
    template <typename T>
    mul_func<T> Idk(int k = 1, int n = N) {
        mul_func<T> idk(n);
        for (int i = 1; i <= n; i++) {
            idk[i] = qpow(i, k);
        }
        return idk;
    }
    // 单位元
    mul_func<int> e(int n = N) {
        mul_func<int> e(n);
        e[1] = 1;
        return e;
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    Dirichlet::init();
    auto phi = Dirichlet::phi();
    auto mu = Dirichlet::mobius();
    auto d = Dirichlet::divisor();
    auto ds = Dirichlet::div_sum();
    auto u = Dirichlet::unit();
    auto id = Dirichlet::Id();
    auto idk = Dirichlet::Idk<i64>(2);
    auto e = Dirichlet::e();
    cout << phi * qpow(u, 2, e) << '\n';
    cout << u * mu << e << '\n';
    return 0;
}