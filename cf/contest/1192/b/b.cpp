#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
int n, q;
ll W;
struct Edge {
    int u, v;
    ll w;
} e[N];

struct Graph {
    struct E {
        int to, nx;
        ll w;
    } e[N << 1];
    int h[N], cnt;
    void init(int n) {
        for (int i = 0; i <= n; ++i) h[i] = -1;
        cnt = -1;
    }
    void addedge(int u, int v, ll w = 0) {
        e[++cnt] = {v, h[u], w};
        h[u] = cnt;
    }
} G;

struct SEG {
    struct node {
        ll val, M, LM, MR, LMR, lazy;
        node() {
            val = M = LM = MR = LMR = lazy = 0;
        }
        void up(ll _lazy) {
            val += _lazy;
            M -= _lazy * 2;
            LM -= _lazy;
            MR -= _lazy;
            lazy += _lazy;
        }
        node operator+(const node &other) const {
            node res = node();
            res.val = max(val, other.val);
            res.M = max(M, other.M);
            res.LM = max(LM, max(other.LM, val + other.M));
            res.MR = max(MR, max(other.MR, M + other.val));
            res.LMR = max(LMR, max(other.LMR, max(LM + other.val, val + other.MR)));
            return res;
        }
    } t[(N * 2) << 2];
    void build(int id, int l, int r) {
        t[id] = node();
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
    }
    void pushdown(int id) {
        ll &lazy = t[id].lazy;
        t[id << 1].up(lazy);
        t[id << 1 | 1].up(lazy);
        lazy = 0;
    }
    void update(int id, int l, int r, int ql, int qr, ll v) {
        if (l >= ql && r <= qr) {
            t[id].up(v);
            return;
        }
        int mid = (l + r) >> 1;
        pushdown(id);
        if (ql <= mid)
            update(id << 1, l, mid, ql, qr, v);
        if (qr > mid)
            update(id << 1 | 1, mid + 1, r, ql, qr, v);
        t[id] = t[id << 1] + t[id << 1 | 1];
    }
} seg;

namespace Tree {
int fa[N], in[N], out[N], r[N << 1];
ll weight[N];
void dfs(int u) {
    r[++*r] = u;
    in[u] = *r;
    for (int i = G.h[u]; ~i; i = G.e[i].nx) {
        int v = G.e[i].to;
        ll w = G.e[i].w;
        if (v == fa[u])
            continue;
        fa[v] = u;
        weight[v] = w;
        dfs(v);
        r[++*r] = u;
    }
    out[u] = *r;
}
void gao() {
    *r = 0;
    dfs(1);
    seg.build(1, 1, *r);
    for (int i = 1; i < n; ++i) {
        if (fa[e[i].u] == e[i].v)
            swap(e[i].u, e[i].v);
        seg.update(1, 1, *r, in[e[i].v], out[e[i].v], weight[e[i].v]);
    }
    ll lst = 0;
    for (int i = 1; i <= q; ++i) {
        int _d;
        ll _w;
        scanf("%d%lld", &_d, &_w);
        _d = (_d + lst) % (n - 1) + 1;
        _w = (_w + lst) % W;
        seg.update(1, 1, *r, in[e[_d].v], out[e[_d].v], _w - weight[e[_d].v]);
        weight[e[_d].v] = _w;
        lst = seg.t[1].LMR;
        printf("%lld\n", lst);
    }
}
}  // namespace Tree

int main() {
    while (scanf("%d%d%lld", &n, &q, &W) != EOF) {
        G.init(n);
        for (int i = 1; i < n; ++i) {
            scanf("%d%d%lld", &e[i].u, &e[i].v, &e[i].w);
            G.addedge(e[i].u, e[i].v, e[i].w);
            G.addedge(e[i].v, e[i].u, e[i].w);
        }
        Tree::gao();
    }
    return 0;
}
