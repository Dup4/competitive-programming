#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define INF 0x3f3f3f3f
#define N 400010
int n, m, Q, K, S, a[N];
struct Edge {
    int u, v, w, a;
    Edge() {}
    void scan() {
        scanf("%d%d%d%d", &u, &v, &w, &a);
    }
    bool operator<(const Edge &other) const {
        return a > other.a;
    }
} e[N];

struct Graph {
    struct node {
        int to, nx, w;
        node() {}
        node(int to, int nx, int w) : to(to), nx(nx), w(w) {}
    } a[N << 1];
    int head[N], pos;
    void init() {
        for (int i = 1; i <= n; ++i) head[i] = -1;
        pos = 0;
    }
    void add(int u, int v, int w) {
        a[pos] = node(v, head[u], w);
        head[u] = pos++;
        a[pos] = node(u, head[v], w);
        head[v] = pos++;
    }
} G;
#define erp(u) \
    for (int it = G.head[u], v = G.a[it].to, w = G.a[it].w; ~it; it = G.a[it].nx, v = G.a[it].to, w = G.a[it].w)

int dis[N];
struct Dijkstra {
    struct node {
        int u, w;
        node() {}
        node(int u, int w) : u(u), w(w) {}
        bool operator<(const node &other) const {
            return w > other.w;
        }
    };
    bool used[N];
    void work() {
        for (int i = 1; i <= n; ++i) {
            dis[i] = INF;
            used[i] = 0;
        }
        dis[1] = 0;
        priority_queue<node> pq;
        pq.push(node(1, 0));
        while (!pq.empty()) {
            int u = pq.top().u;
            pq.pop();
            if (used[u])
                continue;
            used[u] = 1;
            erp(u) if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                pq.push(node(v, dis[v]));
            }
        }
    }
} Dij;

struct SEG {
    struct node {
        int ls, rs;
        int fa, sze, val;
        node() {
            ls = rs = 0;
            fa = 0;
            sze = 1;
            val = 0;
        }
    } t[N * 60];
    int rt[N], tot;
    void init() {
        tot = 0;
        rt[0] = 0;
        t[0] = node();
        for (int i = 1; i <= n; ++i) {
            rt[i] = 0;
        }
    }
    void build(int &id, int l, int r) {
        if (id == 0) {
            id = ++tot;
            t[id] = node();
        }
        if (l == r) {
            t[id].fa = l;
            t[id].val = dis[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(t[id].ls, l, mid);
        build(t[id].rs, mid + 1, r);
    }
    void update(int &now, int pre, int l, int r, int pos, int fa, int sze, int val) {
        int tmp = ++tot;
        t[tmp] = node();
        if (l == r) {
            t[tmp].fa = fa;
            t[tmp].sze = sze;
            t[tmp].val = val;
            now = tmp;
            return;
        }
        t[tmp].ls = t[pre].ls;
        t[tmp].rs = t[pre].rs;
        int mid = (l + r) >> 1;
        if (pos <= mid) {
            update(t[tmp].ls, t[pre].ls, l, mid, pos, fa, sze, val);
        } else {
            update(t[tmp].rs, t[pre].rs, mid + 1, r, pos, fa, sze, val);
        }
        now = tmp;
    }
    node query(int now, int l, int r, int pos) {
        if (l == r) {
            return t[now];
        }
        int mid = (l + r) >> 1;
        if (pos <= mid) {
            return query(t[now].ls, l, mid, pos);
        } else {
            return query(t[now].rs, mid + 1, r, pos);
        }
    }
} seg;

SEG::node find(int k, int x) {
    SEG::node fx = seg.query(seg.rt[k], 1, n, x);
    if (fx.fa == x) {
        return fx;
    } else {
        return find(k, fx.fa);
    }
}

void join(int k, int x, int y) {
    SEG::node fx = find(k, x), fy = find(k, y);
    if (fx.fa != fy.fa) {
        if (fx.sze > fy.sze)
            swap(fx, fy);
        seg.update(seg.rt[k], seg.rt[k], 1, n, fx.fa, fy.fa, fx.sze, min(fx.val, fy.val));
        seg.update(seg.rt[k], seg.rt[k], 1, n, fy.fa, fy.fa, fx.sze + fy.sze, min(fx.val, fy.val));
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        G.init();
        for (int i = 1; i <= m; ++i) {
            e[i].scan();
            G.add(e[i].u, e[i].v, e[i].w);
        }
        Dij.work();
        sort(e + 1, e + 1 + m);
        for (int i = 1; i <= m; ++i) {
            a[m - i + 1] = e[i].a;
        }
        seg.init();
        seg.build(seg.rt[0], 1, n);
        for (int i = 1; i <= m; ++i) {
            seg.rt[i] = seg.rt[i - 1];
            join(i, e[i].u, e[i].v);
        }
        scanf("%d%d%d", &Q, &K, &S);
        ll lastans = 0, v, p;
        while (Q--) {
            scanf("%lld%lld", &v, &p);
            v = (v + K * lastans - 1) % n + 1;
            p = (p + K * lastans) % (S + 1);
            lastans = dis[v];
            int pos = upper_bound(a + 1, a + 1 + m, p) - a;
            if (pos <= m) {
                pos = m - pos + 1;
                SEG::node fv = find(pos, v);
                lastans = fv.val;
            }
            printf("%lld\n", lastans);
        }
    }
    return 0;
}
