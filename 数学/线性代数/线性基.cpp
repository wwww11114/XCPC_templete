#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
// 线性基
template <typename T>
struct LinearBasis {
    constexpr static int W = numeric_limits<T>::digits;
    array<T, W> a;
    bool insert(T x) {
        for (int i = W - 1; i >= 0; i--) {
            if (x >> i & 1) {
                if (a[i]) {
                    x ^= a[i];
                } else {
                    a[i] = x;
                    return true;
                }
            }
        }
        return false;
    }
    T query_max(T res = 0) {
        for (int i = W - 1; i >= 0; i--) {
            res = max(res, res ^ a[i]);
        }
        return res;
    }  
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    
    return 0;
}