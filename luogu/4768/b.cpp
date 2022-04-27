#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define INF 0x3f3f3f3f
#define N 400010
int n, m, Q, K, S;
struct Edge {
    int u, v, w, s;
    Edge() {}
    void scan() {
        scanf("%d%d%d%d", &u, &v, &w, &s);
    }
    bool operator<(const Edge &other) const {
        return s > other.s;
    }
} e[N];

struct Graph {
    struct node {
        int to, nx, w, s;
        node() {}
        node(int to, int nx, int w, int s) : to(to), nx(nx), w(w), s(s) {}
    } a[N << 1];
    int head[N], pos;
    void init() {
        for (int i = 1; i <= (n << 1); ++i) head[i] = -1;
        pos = 0;
    }
    void add(int u, int v, int w, int s = 0) {
        a[pos] = node(v, head[u], w, s);
        head[u] = pos++;
    }
} G;
#define erp(u)                                                                  \
    for (int it = G.head[u], v = G.a[it].to, w = G.a[it].w, s = G.a[it].s; ~it; \
            it = G.a[it].nx, v = G.a[it].to, w = G.a[it].w, s = G.a[it].s)

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

struct MST {
    int fa[N << 1], id;
    int find(int u) {
        return fa[u] == u ? u : fa[u] = find(fa[u]);
    }
    void init() {
        for (int i = 1; i < (n << 1); ++i) {
            fa[i] = i;
        }
        id = n;
    }
    void Kruskal() {
        init();
        G.init();
        for (int i = 1; i <= m; ++i) {
            int u = find(e[i].u), v = find(e[i].v);
            if (u == v)
                continue;
            ++id;
            G.add(id, u, e[i].w, e[i].s);
            G.add(id, v, e[i].w, e[i].s);
            fa[u] = fa[v] = id;
        }
    }
} mst;

int in[N << 1], fin[N << 1], out[N << 1], tim;
int fa[N << 1][20], ss[N << 1][20];
void DFS(int u) {
    if (u <= n) {
        in[u] = ++tim;
        fin[tim] = u;
    } else {
        in[u] = 1e9;
    }
    for (int i = 1; i < 20; ++i) {
        fa[u][i] = fa[fa[u][i - 1]][i - 1];
        ss[u][i] = min(ss[u][i - 1], ss[fa[u][i - 1]][i - 1]);
    }
    erp(u) {
        fa[v][0] = u;
        ss[v][0] = s;
        DFS(v);
        in[u] = min(in[u], in[v]);
    }
    out[u] = tim;
}

int Jump(int u, int r) {
    for (int i = 19; ~i; --i) {
        if (fa[u][i] && ss[u][i] > r) {
            u = fa[u][i];
        }
    }
    return u;
}

struct SEG {
    int Min[N << 3];
    void build(int id, int l, int r) {
        Min[id] = 1e9;
        if (l == r) {
            Min[id] = dis[fin[l]];
            return;
        }
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
        Min[id] = min(Min[id << 1], Min[id << 1 | 1]);
    }
    int query(int id, int l, int r, int ql, int qr) {
        if (l >= ql && r <= qr) {
            return Min[id];
        }
        int mid = (l + r) >> 1;
        int Min = 1e9;
        if (ql <= mid)
            Min = min(Min, query(id << 1, l, mid, ql, qr));
        if (qr > mid)
            Min = min(Min, query(id << 1 | 1, mid + 1, r, ql, qr));
        return Min;
    }
} seg;

void init() {
    G.init();
    tim = 0;
    for (int i = 1; i <= (n << 1); ++i) {
        for (int j = 0; j < 20; ++j) {
            fa[i][j] = 0;
            ss[i][j] = 0;
        }
    }
}
int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        init();
        for (int i = 1; i <= m; ++i) {
            e[i].scan();
            G.add(e[i].u, e[i].v, e[i].w);
            G.add(e[i].v, e[i].u, e[i].w);
        }
        Dij.work();
        sort(e + 1, e + 1 + m);
        mst.Kruskal();
        DFS(mst.id);
        seg.build(1, 1, n);
        scanf("%d%d%d", &Q, &K, &S);
        ll lastans = 0, v, p;
        while (Q--) {
            scanf("%lld%lld", &v, &p);
            v = (v + K * lastans - 1) % n + 1;
            p = (p + K * lastans) % (S + 1);
            int pos = Jump(v, p);
            lastans = seg.query(1, 1, n, in[pos], out[pos]);
            printf("%lld\n", lastans);
        }
    }
    return 0;
}
