#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
// 欧拉函数
i64 get_phi(i64 n) {
    i64 res = n;
    for (int i = 2; i <= n / i; i++) {
        if (n % i == 0) {
            res = res / i * (i - 1);
            while (n % i == 0) {
                n /= i;
            }
        }
    }
    if (n > 1) {
        res = res / n * (n - 1);
    }
    return res;
}
// 线性筛欧拉函数
vector<int> phi, pri;
vector<bool> not_prime;
void pre(i64 n) {
    phi.resize(n + 1);
    not_prime.resize(n + 1);
    not_prime[1] = true;
    phi[1] = 1;
    for (i64 i = 2; i <= n; i++) {
        if (!not_prime[i]) {
            pri.push_back(i);
            phi[i] = i - 1;
        }
        for (i64 pri_j : pri) {
            if (i * pri_j > n) {
                break;
            }
            not_prime[i * pri_j] = true;
            if (i % pri_j == 0) {
                phi[i * pri_j] = phi[i] * pri_j;
                break;
            }
            phi[i * pri_j] = phi[i] * phi[pri_j];
        }
    }
}

int main() { return 0; }