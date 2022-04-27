#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int n, m, w[N], lst;
struct Edge {
    int v, nx;
} e[N << 1];
int h[N];
inline void addedge(int u, int v) {
    e[++*h] = (Edge){v, h[u]};
    h[u] = *h;
}
struct LCA {
    int fa[N], sze[N], son[N], deep[N], top[N];
    void DFS(int u) {
        sze[u] = 1;
        son[u] = 0;
        for (int i = h[u]; i; i = e[i].nx) {
            int v = e[i].v;
            if (v == fa[u])
                continue;
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
        if (son[u])
            gettop(son[u], tp);
        for (int i = h[u]; i; i = e[i].nx) {
            int v = e[i].v;
            if (v == son[u] || v == fa[u])
                continue;
            gettop(v, v);
        }
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
    inline int dis(int u, int v) {
        return deep[u] + deep[v] - 2 * deep[querylca(u, v)];
    }
    inline void init() {
        fa[1] = 1;
        deep[1] = 0;
        DFS(1);
        gettop(1, 1);
    }
} lca;

struct SEG {
    struct node {
        int ls, rs, sum;
        node() {
            sum = ls = rs = 0;
        }
    } t[N << 6];
    int rt[N << 1], tot;
    inline void init() {
        tot = 0;
    }
    void update(int &now, int l, int r, int pos, int v) {
        if (!now)
            now = ++tot, t[now] = node();
        t[now].sum += v;
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        if (pos <= mid)
            update(t[now].ls, l, mid, pos, v);
        else
            update(t[now].rs, mid + 1, r, pos, v);
    }
    int query(int id, int l, int r, int ql, int qr) {
        if (!id)
            return 0;
        if (l >= ql && r <= qr)
            return t[id].sum;
        int mid = (l + r) >> 1;
        int res = 0;
        if (ql <= mid)
            res += query(t[id].ls, l, mid, ql, qr);
        if (qr > mid)
            res += query(t[id].rs, mid + 1, r, ql, qr);
        return res;
    }
} seg;

struct PD_Tree {
    int rt, sum, fa[N], sze[N], f[N], vis[N];
    void getrt(int u, int pre) {
        sze[u] = 1;
        f[u] = 0;
        for (int i = h[u]; i; i = e[i].nx) {
            int v = e[i].v;
            if (vis[v] || v == pre)
                continue;
            getrt(v, u);
            sze[u] += sze[v];
            f[u] = max(f[u], sze[v]);
        }
        f[u] = max(f[u], sum - sze[u]);
        if (f[u] < f[rt])
            rt = u;
    }
    void build(int u) {
        vis[u] = 1;
        for (int i = h[u]; i; i = e[i].nx) {
            int v = e[i].v;
            if (vis[v])
                continue;
            sum = f[0] = sze[v];
            rt = 0;
            getrt(v, u);
            fa[rt] = u;
            build(rt);
        }
    }
    void init() {
        for (int i = 0; i <= n; ++i) vis[i] = 0;
        sum = f[0] = n;
        rt = 0;
        getrt(1, 0);
        fa[rt] = 0;
        build(rt);
    }
    void modify(int u, int w) {
        seg.update(seg.rt[u], 0, n, 0, w);
        for (int x = u; fa[x]; x = fa[x]) {
            int dis = lca.dis(u, fa[x]);
            seg.update(seg.rt[fa[x]], 0, n, dis, w);
            seg.update(seg.rt[n + x], 0, n, dis, w);
        }
    }
    int query(int u, int k) {
        int res = seg.query(seg.rt[u], 0, n, 0, k);
        for (int x = u; fa[x]; x = fa[x]) {
            int dis = lca.dis(u, fa[x]);
            if (dis > k)
                continue;
            res += seg.query(seg.rt[fa[x]], 0, n, 0, k - dis);
            res -= seg.query(seg.rt[n + x], 0, n, 0, k - dis);
        }
        return res;
    }
} pd_tree;

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        for (int i = 0; i <= n; ++i) h[i] = 0;
        for (int i = 1; i <= n; ++i) scanf("%d", w + i);
        for (int i = 1, u, v; i < n; ++i) {
            scanf("%d%d", &u, &v);
            addedge(u, v);
            addedge(v, u);
        }
        lca.init();
        seg.init();
        pd_tree.init();
        for (int i = 1; i <= n; ++i) pd_tree.modify(i, w[i]);
        lst = 0;
        int op, x, y;
        while (m--) {
            scanf("%d%d%d", &op, &x, &y);
            x ^= lst;
            y ^= lst;
            if (op == 0)
                printf("%d\n", lst = pd_tree.query(x, y));
            else
                pd_tree.modify(x, y - w[x]), w[x] = y;
        }
    }
    return 0;
}
