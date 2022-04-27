#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int n, q, deep[N], fa[N], sze[N], top[N], son[N], in[N], fin[N], out[N];
vector<vector<int>> G;

struct SEG {
    struct node {
        int Max, lazy;
        void init() {
            Max = lazy = 0;
        }
        void up(int x) {
            Max += x;
            lazy += x;
        }
        node operator+(const node &other) const {
            node res;
            res.init();
            res.Max = max(Max, other.Max);
            return res;
        }
    } t[N << 2];
    void down(int id) {
        int &lazy = t[id].lazy;
        if (lazy) {
            t[id << 1].up(lazy);
            t[id << 1 | 1].up(lazy);
            lazy = 0;
        }
    }
    void build(int id, int l, int r) {
        t[id].init();
        if (l == r) {
            t[id].Max = deep[fin[l]];
            return;
        }
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
        t[id] = t[id << 1] + t[id << 1 | 1];
    }
    void update(int id, int l, int r, int ql, int qr, int v) {
        if (l >= ql && r <= qr) {
            t[id].up(v);
            return;
        }
        int mid = (l + r) >> 1;
        down(id);
        if (ql <= mid)
            update(id << 1, l, mid, ql, qr, v);
        if (qr > mid)
            update(id << 1 | 1, mid + 1, r, ql, qr, v);
        t[id] = t[id << 1] + t[id << 1 | 1];
    }
    int query(int id, int l, int r, int ql, int qr) {
        if (l >= ql && r <= qr)
            return t[id].Max;
        int mid = (l + r) >> 1;
        down(id);
        int res = 0;
        if (ql <= mid)
            res = max(res, query(id << 1, l, mid, ql, qr));
        if (qr > mid)
            res = max(res, query(id << 1 | 1, mid + 1, r, ql, qr));
        return res;
    }
} seg;

void dfs(int u) {
    sze[u] = 1;
    son[u] = 0;
    for (auto &v : G[u])
        if (v != fa[u]) {
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
    in[u] = ++*in;
    fin[*in] = u;
    if (son[u])
        gettop(son[u], tp);
    for (auto &v : G[u])
        if (v != fa[u] && v != son[u]) {
            gettop(v, v);
        }
    out[u] = *in;
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

struct LCT {
#define ls(x) t[x].son[0]
#define rs(x) t[x].son[1]
    struct node {
        int fa, son[2];
    } t[N];
    bool nrt(int x) {
        return t[t[x].fa].son[0] == x || t[t[x].fa].son[1] == x;
    }
    void rotate(int x) {
        int y = t[x].fa, d = t[y].son[1] == x;
        t[t[y].son[d] = t[x].son[!d]].fa = y;
        if (nrt(y)) {
            t[t[x].fa = t[y].fa].son[t[t[y].fa].son[1] == y] = x;
        } else {
            t[x].fa = t[y].fa;
        }
        t[t[x].son[!d] = y].fa = x;
    }
    void splay(int x) {
        while (nrt(x)) {
            int y = t[x].fa, z = t[y].fa;
            if (nrt(y)) {
                rotate(((t[z].son[1] == y) == (t[y].son[1] == x)) ? y : x);
            }
            rotate(x);
        }
    }
    int bac(int x) {
        if (t[x].son[1] == 0)
            return 0;
        x = t[x].son[1];
        while (t[x].son[0]) x = t[x].son[0];
        return x;
    }
    int pre(int x) {
        while (t[x].son[0]) x = t[x].son[0];
        return x;
    }
    void access(int x) {
        for (int y = 0; x; y = x, x = t[x].fa) {
            splay(x);
            int lp = bac(x);
            if (lp) {
                seg.update(1, 1, n, in[lp], out[lp], 1);
            }
            if (y) {
                lp = pre(y);
                seg.update(1, 1, n, in[lp], out[lp], -1);
            }
            t[x].son[1] = y;
        }
    }
} lct;

int main() {
    while (scanf("%d%d", &n, &q) != EOF) {
        *in = 0;
        G.clear();
        G.resize(n + 1);
        for (int i = 1, u, v; i < n; ++i) {
            scanf("%d%d", &u, &v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        fa[1] = 0;
        deep[1] = 1;
        dfs(1);
        gettop(1, 1);
        seg.build(1, 1, n);
        lct.t[1].fa = 0;
        for (int i = 2; i <= n; ++i) {
            lct.t[i].fa = fa[i];
        }
        int op, x, y;
        while (q--) {
            scanf("%d%d", &op, &x);
            if (op == 1) {
                lct.access(x);
            } else if (op == 2) {
                scanf("%d", &y);
                int lca = querylca(x, y);
                printf("%d\n", seg.query(1, 1, n, in[x], in[x]) + seg.query(1, 1, n, in[y], in[y]) -
                                       2 * seg.query(1, 1, n, in[lca], in[lca]) + 1);
            } else {
                printf("%d\n", seg.query(1, 1, n, in[x], out[x]));
            }
        }
    }
    return 0;
}
