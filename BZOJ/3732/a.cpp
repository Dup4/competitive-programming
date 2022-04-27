#include <bits/stdc++.h>
using namespace std;

#define N 600010
int n, m, q;
struct Edge {
    int u, v, w;
    Edge() {}
    Edge(int u, int v, int w) : u(u), v(v), w(w) {}
    void scan() {
        scanf("%d%d%d", &u, &v, &w);
    }
    bool operator<(const Edge &other) const {
        return w < other.w;
    }
} e[N];

struct Graph {
    struct node {
        int to, nx;
        node() {}
        node(int to, int nx) : to(to), nx(nx) {}
    } a[N << 1];
    int head[N], pos;
    void init() {
        memset(head, -1, sizeof head);
        pos = 0;
    }
    void add(int u, int v) {
        a[pos] = node(v, head[u]);
        head[u] = pos++;
    }
} G;
#define erp(u) for (int it = G.head[u], v = G.a[it].to; ~it; it = G.a[it].nx, v = G.a[it].to)

int a[N];
struct MST {
    int fa[N], id;
    int find(int u) {
        return fa[u] == u ? u : fa[u] = find(fa[u]);
    }
    void init() {
        for (int i = 1; i <= (n << 1); ++i) {
            fa[i] = i;
        }
        id = n;
    }
    void Ksuskal() {
        G.init();
        init();
        for (int i = 1; i <= m; ++i) {
            int u = find(e[i].u), v = find(e[i].v), w = e[i].w;
            if (u == v)
                continue;
            ++id;
            a[id] = w;
            G.add(id, u);
            G.add(id, v);
            fa[u] = fa[v] = id;
        }
    }
} mst;

struct LCA {
    int fa[N], deep[N], son[N], sze[N], top[N];
    void DFS(int u) {
        sze[u] = 1;
        erp(u) {
            fa[v] = u;
            deep[v] = deep[u] + 1;
            DFS(v);
            sze[u] += sze[v];
            if (!son[u] || sze[v] > sze[son[u]])
                son[u] = v;
        }
    }
    void gettop(int u, int tp) {
        top[u] = tp;
        if (!son[u])
            return;
        gettop(son[u], tp);
        erp(u) {
            if (v != son[u]) {
                gettop(v, v);
            }
        }
    }
    void init(int root) {
        memset(son, 0, sizeof son);
        DFS(root);
        gettop(root, root);
    }
    int query(int u, int v) {
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
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= m; ++i) {
        e[i].scan();
    }
    sort(e + 1, e + 1 + m);
    mst.Ksuskal();
    lca.init(mst.id);
    for (int _ = 1, u, v; _ <= q; ++_) {
        scanf("%d%d", &u, &v);
        printf("%d\n", a[lca.query(u, v)]);
    }
    return 0;
}
