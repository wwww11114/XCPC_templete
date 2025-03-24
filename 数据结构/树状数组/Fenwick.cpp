#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
// 区间修改，区间查询
template <typename T>
struct Fenwick {
    vector<T> sum1, sum2;
    const int n;

    Fenwick() = default;
    Fenwick(int n) : n(n + 1), sum1(n + 2), sum2(n + 2) {}
    Fenwick(const vector<T> &v) : n(v.size()), sum1(n + 1), sum2(n + 1) {
        for (int i = 0; i <= n; i++) {
            add(i, v[i]);
        }
    }    

    void range_add(int l, int r, T x) { Add(l + 1, x), Add(r + 2, -x); }
    void add(int p, T x) { return range_add(p, x, x); };
    i64 range_ask(int l, int r) { return Ask(r + 1) - Ask(l); }
    T ask(int p) { return range_ask(p, p); }
private:
    void Add(int p, T x) {
        for (int i = p; i <= n; i += i & -i)
            sum1[i] += x, sum2[i] += x * p;
    }
    T Ask(int p) {
        T res = 0;
        for (int i = p; i; i -= i & -i)
            res += (p + 1) * sum1[i] - sum2[i];
        return res;
    }
};
// 单点修改，区间查询
template <typename T> 
struct Fenwick {
    vector<T> sum;
    const int n;

    Fenwick() = default;
    Fenwick(int n) : n(n + 1), sum(n + 2) {}
    Fenwick(const vector<T> &v) : n(v.size()), sum(n + 2) {
        for (int i = 0; i <= n; i++) {
            add(i, v[i]);
        }
    }
    
    void add(int p, int x) { // 给位置p增加x
        p++;
        while (p <= n)
            sum[p] += x, p += p & -p;
    }
    T ask(int p) { // 求位置p的前缀和
        T res = 0;
        while (p)
            res += sum[p], p -= p & -p;
        return res;
    }
    int range_sum(int l, int r) { // 区间求和
        return ask(r + 1) - ask(l);
    }
};

