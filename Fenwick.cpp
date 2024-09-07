#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
// 区间修改，区间查询
struct Fenwick {
    vector<i64> sum1, sum2;
    i64 n;
    Fenwick(i64 n) : n(n + 1), sum1(n + 2), sum2(n + 2) {}
    void add(i64 p, i64 x) {
        for (int i = p; i <= n; i += i & -i)
            sum1[i] += x, sum2[i] += x * p;
    }
    void range_add(i64 l, i64 r, i64 x) { add(l + 1, x), add(r + 2, -x); }
    i64 ask(i64 p) {
        i64 res = 0;
        for (int i = p; i; i -= i & -i)
            res += (p + 1) * sum1[i] - sum2[i];
        return res;
    }
    i64 range_sum(i64 l, i64 r) { return ask(r + 1) - ask(l); }
};
// 单点修改，区间查询
struct Fenwick {
    vector<int> sum;
    int n;
    Fenwick(int n) : n(n + 1), sum(n + 2) {}
    void add(int p, int x) { // 给位置p增加x
        p++;
        while (p <= n)
            sum[p] += x, p += p & -p;
    }
    int ask(int p) { // 求位置p的前缀和
        int res = 0;
        while (p)
            res += sum[p], p -= p & -p;
        return res;
    }
    int range_ask(int l, int r) { // 区间求和
        return ask(r + 1) - ask(l);
    }
};
