#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pII = pair<int, int>;
#define fi first
#define se second
const int N = 2e4 + 10;
int n, m, q, id;
vector<vector<pII>> G[2];

namespace Tarjan {
int DFN[N], Low[N], fa[N], b[N];
ll sum[N];
void build(int u, int v, int w) {
    ++id;
    int pw, pre = w, i = v;
    while (i != fa[u]) {
        sum[i] = pre;
        pre += b[i];
        i = fa[i];
    }
    sum[id] = sum[u];  //把整个环的边权和存到方点上
    sum[u] = 0;
    i = v;
    while (i != fa[u]) {
        pw = min(sum[i], sum[id] - sum[i]);
        G[1][id].push_back(pII(i, pw));
        G[1][i].push_back(pII(id, pw));
        i = fa[i];
    }
}
void gao(int u, int pre) {
    DFN[u] = Low[u] = ++*DFN;
    int pre_cnt = 0;
    for (auto &it : G[0][u]) {
        int v = it.fi, w = it.se;
        //防止重边
        if (v == pre && pre_cnt == 0) {
            ++pre_cnt;
            continue;
        }
        if (!DFN[v]) {
            //把边权存在v点上
            fa[v] = u, b[v] = w;
            gao(v, u);
            Low[u] = min(Low[u], Low[v]);
        } else {
            Low[u] = min(Low[u], DFN[v]);
        }
        if (Low[v] <= DFN[u])
            continue;
        //圆点之间连边
        G[1][u].push_back(pII(v, w));
        G[1][v].push_back(pII(u, w));
    }
    for (auto &it : G[0][u]) {
        int v = it.fi, w = it.se;
        if (fa[v] == u || DFN[v] <= DFN[u])
            continue;
        //找到非树边 然后建方点并连边
        build(u, v, w);
    }
}
void gogogo() {
    G[1].clear();
    G[1].resize(n * 2 + 1);
    memset(DFN, 0, sizeof DFN);
    memset(sum, 0, sizeof sum);
    gao(1, 0);
}
};  // namespace Tarjan

namespace Tree {
int fa[N], top[N], sze[N], son[N], deep[N];
ll dis[N];
void dfs(int u) {
    sze[u] = 1;
    son[u] = 0;
    for (auto &it : G[1][u]) {
        int v = it.fi, w = it.se;
        if (v == fa[u])
            continue;
        deep[v] = deep[u] + 1;
        fa[v] = u;
        dis[v] = dis[u] + w;
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
    for (auto &it : G[1][u]) {
        int v = it.fi;
        if (v != son[u] && v != fa[u]) {
            gettop(v, v);
        }
    }
}
int querylca(int u, int v) {
    while (top[u] != top[v]) {
        if (deep[top[u]] < deep[top[v]]) {
            swap(u, v);
        }
        u = fa[top[u]];
    }
    if (deep[u] > deep[v])
        swap(u, v);
    return u;
}
int queryson(int u, int f) {
    int res = -1;
    while (top[u] != top[f]) {
        res = top[u];
        u = fa[top[u]];
    }
    return u == f ? res : son[f];
}
void gogogo() {
    memset(dis, 0, sizeof dis);
    fa[1] = 0;
    deep[1] = 0;
    dfs(1);
    gettop(1, 1);
}
};  // namespace Tree

int main() {
    while (scanf("%d%d%d", &n, &m, &q) != EOF) {
        G[0].clear();
        G[0].resize(n + 1);
        id = n;  //点的编号 <= n的点为圆点
        for (int i = 1, u, v, w; i <= m; ++i) {
            scanf("%d%d%d", &u, &v, &w);
            G[0][u].push_back(pII(v, w));
            G[0][v].push_back(pII(u, w));
        }
        Tarjan::gogogo();
        Tree::gogogo();
        while (q--) {
            int u, v;
            scanf("%d%d", &u, &v);
            int lca = Tree::querylca(u, v);
            ll ans = 0;
            if (lca <= n)
                ans = Tree::dis[u] + Tree::dis[v] - Tree::dis[lca] * 2;
            else {
                int A = Tree::queryson(u, lca);
                int B = Tree::queryson(v, lca);
                ans = Tree::dis[u] + Tree::dis[v] - Tree::dis[A] - Tree::dis[B];
                if (Tarjan::sum[A] < Tarjan::sum[B])
                    swap(A, B);
                ans += min(Tarjan::sum[A] - Tarjan::sum[B], Tarjan::sum[lca] + Tarjan::sum[B] - Tarjan::sum[A]);
            }
            printf("%lld\n", ans);
        }
    }
    return 0;
}
