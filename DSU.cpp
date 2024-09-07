#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
struct DSU {
    vector<int> p, sz;
    DSU(int n) : p(n + 1), sz(n + 1, 1) { iota(p.begin(), p.end(), 0); }

    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }

    bool same(int x, int y) { return find(x) == find(y); }

    bool merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y)
            return false;
        if (sz[x] < sz[y])
            swap(x, y);
        sz[x] += sz[y];
        p[y] = x;
        return true;
    }

    int size(int x) { return sz[find(x)]; }
};
