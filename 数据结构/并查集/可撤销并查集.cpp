#include <bits/stdc++.h>
using namespace std;
struct DSU {
    vector<int> p, sz;
    stack<pair<int *, int>> his;
    stack<size_t> ver;

    DSU() = default;
    DSU(int n) : p(n + 1), sz(n + 1, 1) { iota(p.begin(), p.end(), 0); }

    int size(int x) { return sz[find(x)]; }
    size_t version() { return his.size(); }
    bool same(int x, int y) { return find(x) == find(y); }
    int find(int x) {
        while (x != p[x]) {
            x = p[x];
        }
        return x;
    }
    void back_ver(size_t cur = 0) {
        while (his.size() > cur) {
            auto [x, y] = his.top();
            his.pop();
            *x = y;
        }
        while (!ver.empty() && ver.top() >= cur) {
            ver.pop();
        }
        return;
    }
    void rollback(int t = 1) {
        t--;
        while (t--) {
            ver.pop();
        }
        back_ver(ver.top());
        ver.pop();
        return;
    }
    void add_edge(int x, int y) {
        ver.push(version());
        merge(x, y);
        return;
    }

    void change(int &x, int y) {
        if (x != y) {
            his.emplace(&x, x);
            x = y;
        }
        return;
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