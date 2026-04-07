#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

template <typename T, typename Func = function<T(const T &, const T &)>>
struct ST {
    vector<vector<T>> st;
    Func func;
    
    ST() = default;
    ST(const vector<T> &v, Func func = [](const T &a, const T &b) {
        return max(a, b);
    }) : func(move(func)) {
        int k = bit_width<unsigned>(v.size());
        st.resize(k + 1, vector<T>(v.size()));
        st[0] = v;
        for (int i = 0; i < k; i++) {
            for (int j = 0; j + (1 << (i + 1)) - 1 < v.size(); ++j) {
                st[i + 1][j] = this->func(st[i][j], st[i][j + (1 << i)]);
            }
        }
    }
    T range(int l, int r) {
        int t = __lg(r - l + 1);
        return func(st[t][l], st[t][r + 1 - (1 << t)]);
    }
};

//ST表(sparseTable)
//https://www.luogu.com.cn/problem/P3865
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<int> v(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> v[i];
    }
    ST<int> st(v);
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << st.range(l, r) << '\n';
    }
    return 0;
}