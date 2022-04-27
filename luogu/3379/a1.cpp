#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10, M = 20, INF = 0x3f3f3f3f;
int n, q, rt;

struct Graph {
    struct E {
        int to, nx, w;
    } e[N << 1];
    int h[N], cnt;
    void init(int n) {
        for (int i = 1; i <= n; ++i) h[i] = -1;
        cnt = -1;
    }
    void addedge(int u, int v, int w = 0) {
        e[++cnt] = {v, h[u], w};
        h[u] = cnt;
    }
} G;

struct LCA {
    int fa[N], deep[N], dis[N], sze[N], son[N], top[N];
    void dfs(int u) {
        sze[u] = 1;
        son[u] = 0;
        for (int i = h[u]; i; i = e[i].nx) {
            int v = e[i].to, w = e[i].w;
            if (v == fa[u])
                continue;
            fa[v] = u;
            deep[v] = deep[u] + 1;
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
        for (int i = h[u]; i; i = e[i].nx) {
            int v = e[i].to;
            if (v != son[u] && v != fa[u]) {
                gettop(v, v);
            }
        }
    }
    void init(int rt) {
        fa[rt] = rt;
        dfs(rt);
        gettop(rt, rt);
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
} lca;

int main() {
    while (scanf("%d%d%d", &n, &q, &rt) != EOF) {
        G.init(n);
        for (int i = 1, u, v; i < n; ++i) {
            scanf("%d%d", &u, &v);
            G.addedge(u, v);
            G.addedge(v, u);
        }
        lca.init(rt);
        for (int i = 1, u, v; i <= q; ++i) {
            scanf("%d%d", &u, &v);
            printf("%d\n", lca.querylca(u, v));
        }
    }
    return 0;
}
