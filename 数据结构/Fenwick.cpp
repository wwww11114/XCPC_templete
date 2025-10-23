#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
// 区间修改，区间查询
template <typename T>
struct Fenwick {
    int n;
    vector<T> sum1, sum2;

    Fenwick() = default;
    Fenwick(int n) : n(n + 1), sum1(n + 2), sum2(n + 2) {}
    Fenwick(const vector<T> &v) : n(v.size()), sum1(n + 1), sum2(n + 1) {
        for (int i = 1; i <= n; i++) {
            sum1[i] += v[i - 1];
            sum2[i] += v[i - 1] * i;
            if (i + 1 <= n) {
                sum1[i + 1] -= v[i - 1];
                sum2[i + 1] -= v[i - 1] * (i + 1);
            }
            int j = i + (i & -i);
            if (j <= n) {
                sum1[j] += sum1[i];
                sum2[j] += sum2[i];
            }
        }
    }
    void update(int p, T x) {
        return add(p, x - query(p));
    }
    void add(int p, T x) {
        return rangeAdd(p, p, x);
    };
    void rangeAdd(int l, int r, T x) {
        modify(l, x), modify(r + 1, -x);
    }
    T query(int p) {
        return rangeQuery(p, p);
    }
    T rangeQuery(int l, int r) {
        return ask(r) - ask(l - 1);
    }
private:
    void modify(int p, T x) {
        p++;
        for (int i = p; i <= n; i += i & -i) {
            sum1[i] += x;
            sum2[i] += x * p;
        }
    }
    T ask(int p) {
        p++;
        T res{};
        for (int i = p; i; i -= i & -i) {
            res += sum1[i] * (p + 1) - sum2[i];
        }
        return res;
    }
};
// 单点修改，区间查询
template <typename T>
struct Fenwick {
    int n;
    vector<T> sum;

    Fenwick() = default;
    Fenwick(int n) : n(n + 1), sum(n + 2) {}
    Fenwick(const vector<T> &v) : n(v.size()), sum(n + 1) {
        for (int i = 1; i <= n; i++) {
            sum[i] += v[i - 1];
            int j = i + (i & -i);
            if (j <= n) {
                sum[j] += sum[i];
            }
        }
    }
    void add(int p, T x) {
        p++;
        for (; p <= n; p += p & -p) {
            sum[p] += x;
        }
    }
    T ask(int p) {
        p++;
        T res{};
        for (; p; p -= p & -p) {
            res += sum[p];
        }
        return res;
    }
    T query(int p) {
        return rangeQuery(p, p);
    }
    T rangeQuery(int l, int r) {
        return ask(r) - ask(l - 1);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int n, q;
    cin >> n >> q;
    vector<i64> a(n);
    for (auto &i : a) {
        cin >> i;
    }
    Fenwick<i64> fen(a);
    while (q--) {
        int opt;
        cin >> opt;
        if (opt == 1) {
            i64 x, y, k;
            cin >> x >> y >> k;
            x--;
            y--;
            fen.rangeAdd(x, y, k);
        } else {
            int x, y;
            cin >> x >> y;
            x--;
            y--;
            cout << fen.rangeQuery(x, y) << "\n";
        }
    }
}