#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int n, m, q, ans[N];

struct Graph {
    struct E {
        int to, nx;
    } e[N << 2];
    int h[N];
    void init() {
        memset(h, 0, sizeof(h[0]) * (n + 10));
    }
    void addedge(int u, int v) {
        e[++*h] = {v, h[u]};
        h[u] = *h;
    }
} G[2];
#define erp(G, u) for (int o = G.h[u], v = G.e[o].to; o; o = G.e[o].nx, v = G.e[o].to)

struct Tarjan {
    // DFN[i] 点i第一次访问的时间戳
    // Low[i] 点i能访问到的点中的Low的最小值
    // Belong[i] 表示点i在新图中的标号
    // num 表示新图中的点数
    // ptcc[i] 表示第i个点分中的点
    // cut[i]　表示点i是否是割点
    int Low[N], DFN[N], sta[N], num, tot, Belong[N];
    bool cut[N];
    vector<int> ptcc[N];
    void dfs(int u, int pre) {
        Low[u] = DFN[u] = ++*DFN;
        sta[++*sta] = u;
        int pre_cnt = 0, son_cnt = 0;
        erp(G[0], u) {
            //处理重边
            if (v == pre && pre_cnt == 0) {
                pre_cnt++;
                continue;
            }
            if (!DFN[v]) {
                ++son_cnt;
                dfs(v, u);
                Low[u] = min(Low[u], Low[v]);
                //判断割点
                if (u != pre && Low[v] >= DFN[u])
                    cut[u] = 1;
                if (Low[v] >= DFN[u]) {
                    ++tot;
                    int nv;
                    do {
                        nv = sta[(*sta)--];
                        ptcc[tot].push_back(nv);
                    } while (nv != v);
                    ptcc[tot].push_back(u);
                }
            } else {
                Low[u] = min(Low[u], DFN[v]);
            }
        }
        if (u == pre && son_cnt > 1)
            cut[u] = 1;
    }
    void gao() {
        memset(DFN, 0, sizeof(DFN[0]) * (n + 10));
        memset(cut, 0, sizeof(cut[0]) * (n + 10));
        tot = 0;
        for (int i = 0; i <= n; ++i) ptcc[i].clear();
        *sta = 0;
        for (int i = 1; i <= n; ++i)
            if (!DFN[i])
                dfs(i, i);
    }
    void gogogo() {
        G[1].init();
        num = tot;
        //每个割点单独成点
        for (int i = 1; i <= n; ++i) {
            if (cut[i]) {
                Belong[i] = ++num;
            }
        }
        //每个点双单独成点 点双对应的点向点双里面包含的割点连边
        for (int x = 1; x <= tot; ++x) {
            for (int j = 0, sze = ptcc[x].size(); j < sze; ++j) {
                int y = ptcc[x][j];
                if (cut[y]) {
                    G[1].addedge(x, Belong[y]);
                    G[1].addedge(Belong[y], x);
                } else {
                    Belong[y] = x;
                }
            }
        }
    }
} tarjan;

namespace Tree {
int fa[N], deep[N], sze[N], top[N], son[N];
int f[N];
void dfs(int u) {
    sze[u] = 1;
    son[u] = 0;
    erp(G[1], u) if (v != fa[u]) {
        fa[v] = u;
        deep[v] = deep[u] + 1;
        dfs(v);
        sze[u] += sze[v];
        if (!son[u] || sze[v] > sze[son[u]])
            son[u] = v;
    }
}
void gettop(int u, int tp) {
    top[u] = tp;
    if (son[u])
        gettop(son[u], tp);
    erp(G[1], u) if (v != son[u] && v != fa[u]) gettop(v, v);
}
int querylca(int u, int v) {
    while (top[u] != top[v]) {
        if (deep[top[u]] < deep[top[v]])
            swap(u, v);
        u = fa[top[u]];
    }
    if (deep[u] > deep[v])
        swap(u, v);
    return u;
}
void init() {
    fa[1] = 0;
    deep[1] = 0;
    dfs(1);
    gettop(1, 1);
    memset(f, 0, sizeof(f[0]) * (n + 10));
}
void add(int u, int v) {
    int lca = querylca(u, v);
    ++f[u];
    ++f[v];
    --f[lca];
    if (fa[lca])
        --f[fa[lca]];
}
void build(int u) {
    erp(G[1], u) if (v != fa[u]) {
        build(v);
        f[u] += f[v];
    }
}
};  // namespace Tree

int main() {
    while (scanf("%d%d%d", &n, &m, &q) != EOF) {
        memset(ans, 0, sizeof(ans[0]) * (n + 10));
        G[0].init();
        for (int i = 1, u, v; i <= m; ++i) {
            scanf("%d%d", &u, &v);
            G[0].addedge(u, v);
            G[0].addedge(v, u);
        }
        tarjan.gao();
        tarjan.gogogo();
        Tree::init();
        int u, v;
        while (q--) {
            scanf("%d%d", &u, &v);
            ++ans[u];
            ++ans[v];
            Tree::add(tarjan.Belong[u], tarjan.Belong[v]);
        }
        Tree::build(1);
        for (int i = 1; i <= n; ++i) {
            if (tarjan.cut[i]) {
                printf("%d\n", Tree::f[tarjan.Belong[i]]);
            } else {
                printf("%d\n", ans[i]);
            }
        }
    }
    return 0;
}
