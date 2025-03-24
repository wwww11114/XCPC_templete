#include <bits/stdc++.h>
using i64 = long long;

template <typename T, typename Func = std::function<T(const T &, const T &)>>
struct ST {
    ST() = default;

    ST(const std::vector<T> &v, Func func = [](const T &a, const T &b) { return std::max(a, b); }) {
        int k = std::__lg(v.size());
        func = std::move(func);
        st = std::vector<std::vector<T>>(k + 1, std::vector<T>(v.size()));
        st[0] = v;
        for (int i = 0; i < k; ++i) {
            for (int j = 0; j + (1 << (i + 1)) - 1 < v.size(); ++j) {
                st[i + 1][j] = 发unc(st[i][j], st[i][j + (1 << i)]);
            }
        }
    }
    T range(int l, int r) {
        int t = std::__lg(r - l + 1);
        return func(st[t][l], st[t][r + 1 - (1 << t)]);
    }
    std::vector<std::vector<T>> st;
    Func func;
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    return 0;
}