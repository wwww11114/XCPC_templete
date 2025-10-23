#include <bits/stdc++.h>
using namespace std;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using f64 = long double;
using i128 = __int128_t;
using u128 = __uint128_t;
struct myhash {
    static u64 hash(u64 x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(u64 x) const {
        static const u64 SEED = chrono::steady_clock::now().time_since_epoch().count();
        return hash(x + SEED);
    }
    size_t operator()(pair<u64, u64> x) const {
        static const u64 SEED = chrono::steady_clock::now().time_since_epoch().count();
        return hash(x.first + SEED) ^ (hash(x.second + SEED) >> 1);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;

    return 0;
}