#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n, q, a[N];
int fa[N], deep[N], sze[N], son[N], p[N], fp[N], top[N], p_cnt;
struct Edge {
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
        a[pos] = node(u, head[v]);
        head[v] = pos++;
    }
} G;
#define erp(u) for (int it = G.head[u], v = G.a[it].to; ~it; it = G.a[it].nx, v = G.a[it].to)
struct SEG {
    struct node {
        int l, r, cnt, lazy;
        node() {
            l = r = -1;
            cnt = 0;
            lazy = -1;
        }
        void add(int c) {
            l = r = c;
            cnt = 1;
            lazy = c;
        }
        node operator+(const node &other) const {
            node res = node();
            res.l = l, res.r = other.r;
            res.cnt = cnt + other.cnt;
            if (r != -1 && other.l != -1 && r == other.l) {
                --res.cnt;
            }
            return res;
        }
    } t[N << 2], res[2];
    void build(int id, int l, int r) {
        if (l == r) {
            t[id].l = t[id].r = a[fp[l]];
            t[id].cnt = 1;
            return;
        }
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
        t[id] = t[id << 1] + t[id << 1 | 1];
    }
    void pushdown(int id) {
        int &C = t[id].lazy;
        if (C == -1) {
            return;
        }
        t[id << 1].add(C);
        t[id << 1 | 1].add(C);
        C = -1;
    }
    void update(int id, int l, int r, int ql, int qr, int c) {
        if (l >= ql && r <= qr) {
            t[id].add(c);
            return;
        }
        int mid = (l + r) >> 1;
        pushdown(id);
        if (ql <= mid)
            update(id << 1, l, mid, ql, qr, c);
        if (qr > mid)
            update(id << 1 | 1, mid + 1, r, ql, qr, c);
        t[id] = t[id << 1] + t[id << 1 | 1];
    }
    void query(int id, int l, int r, int ql, int qr, node &res) {
        if (l >= ql && r <= qr) {
            res = t[id] + res;
            return;
        }
        int mid = (l + r) >> 1;
        pushdown(id);
        if (qr > mid)
            query(id << 1 | 1, mid + 1, r, ql, qr, res);
        if (ql <= mid)
            query(id << 1, l, mid, ql, qr, res);
    }
} seg;

void DFS(int u) {
    sze[u] = 1;
    erp(u) if (v != fa[u]) {
        fa[v] = u;
        deep[v] = deep[u] + 1;
        DFS(v);
        sze[u] += sze[v];
        if (!son[u] || sze[v] > sze[son[u]]) {
            son[u] = v;
        }
    }
}
void gettop(int u, int sp) {
    top[u] = sp;
    p[u] = ++p_cnt;
    fp[p_cnt] = u;
    if (!son[u]) {
        return;
    }
    gettop(son[u], sp);
    erp(u) if (v != son[u] && v != fa[u]) {
        gettop(v, v);
    }
}
void update(int u, int v, int c) {
    while (top[u] != top[v]) {
        if (deep[top[u]] < deep[top[v]]) {
            swap(u, v);
        }
        seg.update(1, 1, n, p[top[u]], p[u], c);
        u = fa[top[u]];
    }
    if (deep[u] > deep[v]) {
        swap(u, v);
    }
    seg.update(1, 1, n, p[u], p[v], c);
}
int query(int u, int v) {
    int id = 0;
    seg.res[0] = SEG::node();
    seg.res[1] = SEG::node();
    while (top[u] != top[v]) {
        if (deep[top[u]] < deep[top[v]]) {
            swap(u, v);
            id ^= 1;
        }
        seg.query(1, 1, n, p[top[u]], p[u], seg.res[id]);
        u = fa[top[u]];
    }
    if (deep[u] > deep[v]) {
        swap(u, v);
        id ^= 1;
    }
    id ^= 1;
    seg.query(1, 1, n, p[u], p[v], seg.res[id]);
    swap(seg.res[0].l, seg.res[0].r);
    return (seg.res[0] + seg.res[1]).cnt;
}

void init() {
    G.init();
    memset(son, 0, sizeof son);
    p_cnt = 0;
}
int main() {
    while (scanf("%d%d", &n, &q) != EOF) {
        init();
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
        }
        for (int i = 1, u, v; i < n; ++i) {
            scanf("%d%d", &u, &v);
            G.add(u, v);
        }
        DFS(1);
        gettop(1, 1);
        seg.build(1, 1, n);
        char op[10];
        int a, b, c;
        while (q--) {
            scanf("%s%d%d", op, &a, &b);
            switch (op[0]) {
                case 'C':
                    scanf("%d", &c);
                    update(a, b, c);
                    break;
                case 'Q':
                    printf("%d\n", query(a, b));
                    break;
                default:
                    assert(0);
            }
        }
    }
    return 0;
}
