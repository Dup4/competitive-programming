#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e5 + 10;
const int M = 20;
int n, m, w[N], lst;
struct Edge {
    int v, nx;
} e[N << 1];
int h[N];
inline void addedge(int u, int v) {
    e[++*h] = {v, h[u]};
    h[u] = *h;
}
struct LCA {
    int F[N << 1], P[N];
    struct RMQ {
        int Min[N << 1][M];
        int mm[N << 1], rmq[N << 1];
        void init(int n) {
            mm[0] = -1;
            for (int i = 1; i <= n; ++i) {
                mm[i] = ((i & (i - 1)) == 0) ? mm[i - 1] + 1 : mm[i - 1];
                Min[i][0] = i;
            }
            for (int j = 1; j <= mm[n]; ++j) {
                for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
                    Min[i][j] = rmq[Min[i][j - 1]] < rmq[Min[i + (1 << (j - 1))][j - 1]]
                                        ? Min[i][j - 1]
                                        : Min[i + (1 << (j - 1))][j - 1];
                }
            }
        }
        int queryMin(int x, int y) {
            if (x > y)
                swap(x, y);
            int k = mm[y - x + 1];
            return rmq[Min[x][k]] <= rmq[Min[y - (1 << k) + 1][k]] ? Min[x][k] : Min[y - (1 << k) + 1][k];
        }
    } st;
    int dep[N];
    void DFS(int u, int pre) {
        F[++*F] = u;
        st.rmq[*F] = dep[u];
        P[u] = *F;
        for (int i = h[u]; i; i = e[i].nx) {
            int v = e[i].v;
            if (v == pre)
                continue;
            dep[v] = dep[u] + 1;
            DFS(v, u);
            F[++*F] = u;
            st.rmq[*F] = dep[u];
        }
    }
    void init(int root, int node_num) {
        *F = 0;
        dep[root] = 0;
        DFS(root, root);
        st.init(2 * node_num - 1);
    }
    int query(int u, int v) {
        return F[st.queryMin(P[u], P[v])];
    }
    int dis(int u, int v) {
        return dep[u] + dep[v] - 2 * dep[query(u, v)];
    }
} lca;

struct SEG {
    struct node {
        int ls, rs, sum;
        node() {
            sum = ls = rs = 0;
        }
        node operator+(const node &other) const {
            node res = node();
            res.sum = sum + other.sum;
            return res;
        }
    } t[N * 60];
    int rt[N << 1], tot;
    inline void init() {
        tot = 0;
        memset(rt, 0, sizeof rt);
    }
    inline void up(int id) {
        int ls = t[id].ls, rs = t[id].rs;
        t[id].sum = 0;
        if (ls)
            t[id].sum += t[ls].sum;
        if (rs)
            t[id].sum += t[rs].sum;
    }
    void update(int &now, int l, int r, int pos, int v) {
        if (!now)
            now = ++tot, t[now] = node();
        if (l == r) {
            t[now].sum += v;
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid)
            update(t[now].ls, l, mid, pos, v);
        else
            update(t[now].rs, mid + 1, r, pos, v);
        up(now);
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
        memset(vis, 0, sizeof vis);
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
        memset(h, 0, sizeof h);
        for (int i = 1; i <= n; ++i) scanf("%d", w + i);
        for (int i = 1, u, v; i < n; ++i) {
            scanf("%d%d", &u, &v);
            addedge(u, v);
            addedge(v, u);
        }
        lca.init(1, n);
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
