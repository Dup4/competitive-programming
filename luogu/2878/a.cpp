#include <bits/stdc++.h>
using namespace std;
const int N = 1e3, M = 1e6 + 10;
int n, m, g[N][N], can[N];
struct Edge {
    int v, nx;
} e[M << 1];
int h[N], tot;
inline void addedge(int u, int v) {
    e[tot] = {v, h[u]};
    h[u] = tot++;
}

//染色判断二分图
struct ISBG {
    int ok[N], color[N];
    bool dfs(int u, int col) {
        color[u] = col;
        for (int i = h[u]; ~i; i = e[i].nx) {
            int v = e[i].v;
            if (!ok[v])
                continue;
            if (color[v] != -1) {
                if (color[v] == col)
                    return false;
                continue;
            }
            if (!dfs(v, col ^ 1))
                return false;
        }
        return true;
    }
} isbg;

struct Tarjan {
    // DFN[i] 点i第一次访问的时间戳
    // Low[i] 点i能访问到的点中的Low的最小值
    int Low[N], DFN[N], sta[N];
    bool Insta[N];
    vector<vector<int>> ptcc;
    void dfs(int u, int pre) {
        Low[u] = DFN[u] = ++*Low;
        sta[++*sta] = u;
        Insta[u] = 1;
        int pre_cnt = 0;
        for (int i = h[u]; ~i; i = e[i].nx) {
            int v = e[i].v;
            if (v == pre && pre_cnt == 0) {
                pre_cnt++;
                continue;
            }
            if (!DFN[v]) {
                dfs(v, u);
                Low[u] = min(Low[u], Low[v]);
                if (Low[v] >= DFN[u]) {
                    vector<int> vec;
                    int nv;
                    do {
                        nv = sta[(*sta)--];
                        vec.push_back(nv);
                        Insta[nv] = false;
                    } while (nv != v);
                    vec.push_back(u);
                    ptcc.push_back(vec);
                }
            } else {
                Low[u] = min(Low[u], DFN[v]);
            }
        }
    }
    void gao(int n) {
        memset(DFN, 0, sizeof(DFN[0]) * (n + 10));
        memset(Insta, 0, sizeof(Insta[0]) * (n + 10));
        ptcc.clear();
        *sta = *Low = 0;
        for (int i = 1; i <= n; ++i)
            if (!DFN[i])
                dfs(i, i);
    }
    void gogogo() {
        for (auto &vec : ptcc) {
            for (auto &it : vec) {
                isbg.ok[it] = 1;
                isbg.color[it] = -1;
            }
            if (!isbg.dfs(vec[0], 0)) {
                for (auto &it : vec) {
                    can[it] = 1;
                }
            }
            for (auto &it : vec) {
                isbg.ok[it] = 0;
            }
        }
    }
} tarjan;

int main() {
    while (scanf("%d%d", &n, &m), n + m) {
        tot = 0;
        for (int i = 1; i <= n; ++i) {
            h[i] = -1;
            can[i] = 0;
            for (int j = 1; j <= n; ++j)
                if (i != j) {
                    g[i][j] = 1;
                }
        }
        for (int i = 1, u, v; i <= m; ++i) {
            scanf("%d%d", &u, &v);
            assert(u != v);
            g[u][v] = g[v][u] = 0;
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j)
                if (i != j && g[i][j]) {
                    addedge(i, j);
                }
        }
        tarjan.gao(n);
        tarjan.gogogo();
        int res = 0;
        for (int i = 1; i <= n; ++i) res += can[i];
        printf("%d\n", n - res);
    }
    return 0;
}
