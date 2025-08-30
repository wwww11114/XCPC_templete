#include <bits/stdc++.h>
using namespace std;
// 有向图欧拉回路or通路
struct Euler {
    vector<int> in, out;     // 存储入,出度
    vector<vector<int>> gra; // 存储图
    int n;
    // 初始化
    Euler() = default;
    Euler(int n) : n(n), gra(n), in(n), out(n) {}
    // 添加边
    void add_edge(int u, int v) {
        gra[u].push_back(v);
        out[u]++;
        in[v]++;
    }
    // 判断是否存在欧拉通路and返回起点
    int is_semiEuler() {
        int odd = 0, neodd = 0, start = 0;
        for (int i = 1; i <= n; i++) {
            if (out[i] - in[i] == 1) {
                odd++;
                start = i;
            } else if (in[i] - out[i] == 1) {
                neodd++;
            } else if (in[i] != out[i]) {
                return 0;
            }
        }
        if (odd == 1 && neodd == 1) {
            return start;
        }
        if (odd == 0 && neodd == 0) {
            return 1;
        }
        return 0;
    }
    // 判断是否存在欧拉回路
    bool is_Euler() {
        for (int i = 1; i <= n; i++) {
            if (in[i] != out[i]) {
                return false;
            }
        }
        return true;
    }
    // 求解欧拉回路or通路
    vector<int> Euler_tour(int start) {
        vector<int> tour;
        auto dfs = [&](auto &&dfs, int u) -> void {
            while (!gra[u].empty()) {
                int v = gra[u].back();
                gra[u].pop_back();
                dfs(dfs, v);
            }
            tour.push_back(u);
        };
        dfs(dfs, start);
        return tour; // 返回的是逆序的欧拉回路or通路
    }
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    return 0;
}