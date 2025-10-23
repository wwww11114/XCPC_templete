#include <bits/stdc++.h>
using namespace std;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using f64 = long double;
using i128 = __int128_t;
using u128 = __uint128_t;
vector<int> pri;
vector<bool> not_prime;
void pre(int n) {
    not_prime.resize(n + 1);
    not_prime[0] = not_prime[1] = true;
    for (int i = 2; i <= n; ++i) {
        if (!not_prime[i]) {
            pri.push_back(i);
        }
        for (int pri_j : pri) {
            if (i * pri_j > n) {
                break;
            }
            not_prime[i * pri_j] = true;
            if (i % pri_j == 0) {
                break;
            }
        }
    }
}

i64 min25_sieve(i64 n) {
    int sqn = sqrtl(n);
    pre(sqn);
    // 预处理下标
    vector<i64> v;
    for (i64 i = n; i >= 1; i = n / (n / i + 1)) {
        v.push_back(n / i);
    }
    vector<int> id1(sqn + 1), id2(sqn + 1);
    for (int i = 0; i < v.size(); i++) {
        if (v[i] <= sqn) {
            id1[v[i]] = i;
        } else {
            id2[n / v[i]] = i;
        }
    }
    auto id = [&](i64 x) -> int {
        return x <= sqn ? id1[x] : id2[n / x];
    };
    // 求解G函数
    // G:小于n的质数的F(x)和
    // F为多项式F(x)
    // SF为2 - n的F(x)的和
    auto solve_G = [&](auto F, auto SF) {
        vector<i64> G(v.size());
        for (auto i : v) {
            G[id(i)] = SF(i);
        }
        i64 pre = 0;
        for (auto p : pri) {
            if (v.back() < 1ll * p * p) {
                break;
            }
            for (int it = (int)v.size() - 1; v[it] >= 1ll * p * p; it--) {
                i64 i = v[it];
                G[id(i)] -= F(p) * (G[id(i / p)] - pre );
            }
            pre += F(p);
        }
        return G;
    };
    // 求解2-n的F(x)的和
    auto solve_S = [&](vector<i64> &G, auto F) -> i64 {
        //设S(n,x)表示求2到n中所有最小质因子大于p_x的F(x)之和
        auto dfs = [&](auto &&dfs, i64 n, int x, i64 pre) -> i64 {
            if (x && pri[x - 1] >= n) {
                return 0;
            }
            i64 ans = G[id(n)] - pre;
            for (int i = x + 1; i <= pri.size() && 1ll * pri[i - 1] * pri[i - 1] <= n; i++) {
                pre += F(pri[i - 1]);
                for (i64 p = pri[i - 1]; p <= n; p *= pri[i - 1]) {
                    ans += F(p) * (dfs(dfs, n / p, i, pre) + (p != pri[i - 1]));
                }
            }
            return ans;
        };
        return (dfs(dfs, n, 0, 0) + 1);
    };

    auto G = solve_G(
        [](i64 x) {
        return 1;
    },
        [](i64 x) {
        return x - 1;
    }
    );
    i64 ans = solve_S(G, [](i64 x) {
        return 1;
    });
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    i64 n;
    cin >> n;
    cout << min25_sieve(n) << "\n";
    return 0;
}