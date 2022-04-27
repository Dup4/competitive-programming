#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int n, m, q;

int val[N];
struct Edge {
    int u, v, w;
    bool operator<(const Edge &other) const {
        return w > other.w;
    }
} e[N];

struct Graph {
    struct E {
        int to, nx;
    } e[N << 1];
    int h[N], cnt;
    void init(int n) {
        for (int i = 1; i <= n; ++i) h[i] = -1;
        cnt = -1;
    }
    void addedge(int u, int v) {
        e[++cnt] = {v, h[u]};
        h[u] = cnt;
    }
} G;

struct MST {
    int fa[N], id;
    int find(int x) {
        return fa[x] == 0 ? x : fa[x] = find(fa[x]);
    }
    void init(int n) {
        for (int i = 1; i <= n * 2; ++i) fa[i] = 0;
        id = n;
    }
    void gao(int n) {
        G.init(n * 2);
        init(n);
        sort(e + 1, e + 1 + m);
        for (int i = 1; i <= m; ++i) {
            int u = find(e[i].u), v = find(e[i].v), w = e[i].w;
            if (u == v)
                continue;
            ++id;
            val[id] = w;
            G.addedge(id, u);
            G.addedge(id, v);
            fa[u] = fa[v] = id;
        }
    }
} mst;

struct LCA {
    int fa[N], deep[N], sze[N], son[N], top[N];
    void dfs(int u) {
        sze[u] = 1;
        son[u] = 0;
        for (int i = G.h[u]; ~i; i = G.e[i].nx) {
            int v = G.e[i].to;
            if (v == fa[u])
                continue;
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
        for (int i = G.h[u]; ~i; i = G.e[i].nx) {
            int v = G.e[i].to;
            if (v != son[u] && v != fa[u]) {
                gettop(v, v);
            }
        }
    }
    void init(int n) {
        for (int i = 1; i <= n; ++i) {
            if (mst.fa[i] == 0) {
                fa[i] = i;
                dfs(i);
                gettop(i, i);
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
} lca;

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v, w; i <= m; ++i) {
        scanf("%d%d%d", &u, &v, &w);
        e[i] = {u, v, w};
    }
    mst.gao(n);
    lca.init(mst.id);
    scanf("%d", &q);
    for (int _ = 1, u, v; _ <= q; ++_) {
        scanf("%d%d", &u, &v);
        if (mst.find(u) != mst.find(v))
            puts("-1");
        else
            printf("%d\n", val[lca.querylca(u, v)]);
    }
    return 0;
}
