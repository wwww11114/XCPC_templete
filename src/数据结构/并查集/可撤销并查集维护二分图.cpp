#include <bits/stdc++.h>
using namespace std;
struct DSU {
    vector<int> p, sz, f;
    stack<pair<int &, int>> his;
    int n;

    DSU() = default;
    DSU(int n) : n(n), p(2 * n + 1), sz(2 * n + 1, 1), f(2 * n + 1, 1) { iota(p.begin(), p.end(), 0); }

    int version() { return his.size(); }
    int size(int x) { return sz[find(x)]; }
    bool query(int x = 0) { return f[find(x)]; }
    bool same(int x, int y) { return find(x) == find(y); }
    int find(int x) {
        while (x != p[x]) {
            x = p[x];
        }
        return x;
    }
    void add_edge(int x, int y) {
        merge(x, y + n);
        merge(x + n, y);
        check(x, x + n);
        check(y, y + n);
    }
    void back_ver(int cur = 0) {
        while (his.size() > cur) {
            auto [x, y] = his.top();
            his.pop();
            x = y;
        }
    }

    void change(int &x, int y) {
        if (x != y) {
            his.emplace(x, x);
            x = y;
        }
    }
    void check(int x, int y) {
        if (!same(x, y))
            return;
        change(f[find(x)], 0);
        change(f[0], 0);
    }
    bool merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y)
            return false;
        if (sz[x] < sz[y])
            swap(x, y);
        change(sz[x], sz[x] + sz[y]);
        change(p[y], x);
        return true;
    }
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    return 0;
}