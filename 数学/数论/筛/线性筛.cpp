#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    pre(1e6);
    return 0;
}