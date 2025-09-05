#include <bits/stdc++.h>
using namespace std;
struct RDSU {
    vector<int> p, sz;
    stack<pair<int &, int>> his;

    RDSU() = default;
    RDSU(int n) : p(n + 1), sz(n + 1, 1) { 
        iota(p.begin(), p.end(), 0); 
    }

    int size(int x) { return sz[find(x)]; }
    int version() { return his.size(); }
    bool same(int x, int y) { return find(x) == find(y); }
    int find(int x) {
        while (x != p[x]) {
            x = p[x];
        }
        return x;
    }
    void rollback(int cur) {
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
    bool merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) {
            return false;
        }
        if (sz[x] < sz[y]) {
            swap(x, y);
        }
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