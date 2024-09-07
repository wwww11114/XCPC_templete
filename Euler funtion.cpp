#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
i64 get_phi(i64 n) {
    i64 res = n;
    for (i64 i = 2; i <= n / i; i++) {
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
int main() { return 0; }