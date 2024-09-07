#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
constexpr int N = 1e6 + 1;
vector<int> pri;
bool not_prime[N];
void pre(int n) {
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
void solve() {
    i64 n;
    cin >> n;
    return;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    i64 T = 1;
    cin >> T;
    pre(1e6);
    while (T--) {
        solve();
    }
    return 0;
}