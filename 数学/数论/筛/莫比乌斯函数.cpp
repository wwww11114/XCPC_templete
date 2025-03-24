#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
vector<int> mu, pri;
vector<bool> not_prime;
void pre(i64 n) {
    mu.resize(n + 1);
    not_prime.resize(n + 1);
    not_prime[1] = true;
    mu[1] = 1;
    for (i64 i = 2; i <= n; i++) {
        if (!not_prime[i]) {
            pri.push_back(i);
            mu[i] = -1;
        }
        for (i64 pri_j : pri) {
            if (i * pri_j > n) {
                break;
            }
            not_prime[i * pri_j] = true;
            if (i % pri_j == 0) {
                break;
            }
            mu[i * pri_j] = -mu[i];
        }
    }
}
