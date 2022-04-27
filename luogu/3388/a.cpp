#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
int n, m;
struct Edge {
    int v, nx, cut;
} e[N << 1];
int h[N], tot;
inline void addedge(int u, int v) {
    e[tot] = {v, h[u], 0};
    h[u] = tot++;
}
struct Tarjan {
    // DFN[i] 点i第一次访问的时间戳
    // Low[i] 点i能访问到的点中的Low的最小值
    // cut[i] 点i是否是割点
    int Low[N], DFN[N], add_block[N], cut[N], bridge;
    bool Insta[N];
    void dfs(int u, int pre) {
        Low[u] = DFN[u] = ++*Low;
        Insta[u] = 1;
        int son = 0;
        int pre_cnt = 0;
        for (int i = h[u]; ~i; i = e[i].nx) {
            int v = e[i].v;
            //处理重边
            if (v == pre && pre_cnt == 0) {
                pre_cnt++;
                continue;
            }
            if (!DFN[v]) {
                ++son;
                dfs(v, u);
                Low[u] = min(Low[u], Low[v]);
                //桥
                //一条(u, v)是桥，当且仅当(u, v)为树枝边，且满足DFN[u] < Low[v]
                if (Low[v] > DFN[u]) {
                    ++bridge;
                    e[i].cut = 1;
                    e[i ^ 1].cut = 1;
                }
                //割点
                //一个顶点u是割点，当且仅当
                // 1. u 为树根，且u有多余一个子树
                // 2. u 不为树根，满足存在(u, v)为树枝边，即u为v在搜索树中的父亲，使得DFN[u] <= Low[v]
                if (u != pre && Low[v] >= DFN[u]) {
                    cut[u] = 1;
                    ++add_block[u];
                }
            } else
                Low[u] = min(Low[u], DFN[v]);
        }
        if (u == pre && son > 1)
            cut[u] = 1;
        if (u == pre)
            add_block[u] = son - 1;
        Insta[u] = 0;
    }
    void gao(int n) {
        memset(DFN, 0, sizeof(DFN[0]) * (n + 10));
        memset(Insta, 0, sizeof(Insta[0]) * (n + 10));
        *Low = 0;
        for (int i = 1; i <= n; ++i)
            if (!DFN[i])
                dfs(i, i);
    }
    void gogogo() {
        vector<int> vec;
        for (int i = 1; i <= n; ++i)
            if (cut[i])
                vec.push_back(i);
        int sze = vec.size();
        printf("%d\n", sze);
        for (int i = 0; i < sze; ++i) printf("%d%c", vec[i], " \n"[i == sze - 1]);
    }
} tarjan;

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        tot = 0;
        memset(h, -1, sizeof(h[0]) * (n + 10));
        for (int i = 1, u, v; i <= m; ++i) {
            scanf("%d%d", &u, &v);
            addedge(u, v);
            addedge(v, u);
        }
        tarjan.gao(n);
        tarjan.gogogo();
    }
    return 0;
}
