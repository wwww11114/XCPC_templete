#include <bits/stdc++.h>
using namespace std;
// 无向图欧拉回路or通路
struct Euler {
    int id = 0;
    vector<int> edg;           // 存储边
    vector<vector<int>> gra; // 存储图
    // 初始化
    Euler(int n, int m) {
        gra.resize(n + 1);
    }
    // 添加边
    void add_edge(int u, int v) {
        gra[u].push_back(id);
        gra[v].push_back(id);
        edg.push_back(u ^ v);
        id++;
    }
    // 判断是否存在欧拉通路and返回起点
    int is_semiEuler() {
        int n = gra.size() - 1;
        int odd = 0, start = 0;
        for (int i = 1; i <= n; i++) {
            if (gra[i].size() & 1) {
                odd++;
                start = i;
            }
        }
        if (odd == 0)
            return 1;
        if (odd == 2)
            return start;
        return 0;
    }
    // 判断是否存在欧拉回路
    bool is_Euler() {
        int n = gra.size() - 1;
        for (int i = 1; i <= n; i++) {
            if (gra[i].size() & 1)
                return false;
        }
        return true;
    }
    // 求解欧拉回路or通路
    vector<int> Euler_tour(int start) {
        vector<int> tour;
        function<void(int)> dfs = [&](int u) {
            while (!gra[u].empty()) {
                int i = gra[u].back();
                gra[u].pop_back();
                if (edg[i] == -1)
                    continue;
                int v = edg[i] ^ u;
                edg[i] = -1;
                dfs(v);
            }
            tour.push_back(u);
        };
        dfs(start);
        return tour;
    }
};
