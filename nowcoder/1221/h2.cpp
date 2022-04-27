#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define N 200010
#define DEG 25
int n, m;
struct Edge {
    int u, v, w, vis;
    void scan() {
        scanf("%d%d%d", &u, &v, &w);
        vis = 0;
    }
    bool operator<(const Edge &other) const {
        return w < other.w;
    }
} edge[N];
struct Graph {
    struct node {
        int to, nx, w;
        node() {}
        node(int to, int nx, int w) : to(to), nx(nx), w(w) {}
    } a[N << 1];
    int head[N], pos;
    void init() {
        memset(head, 0, sizeof head);
        pos = 0;
    }
    void add(int u, int v, int w) {
        a[++pos] = node(v, head[u], w);
        head[u] = pos;
        a[++pos] = node(u, head[v], w);
        head[v] = pos;
    }
} G;
#define erp(u) \
    for (int it = G.head[u], v = G.a[it].to, w = G.a[it].w; it; it = G.a[it].nx, v = G.a[it].to, w = G.a[it].w)

int pre[N];
int find(int x) {
    return pre[x] == 0 ? x : pre[x] = find(pre[x]);
}
void Kruskal() {
    memset(pre, 0, sizeof pre);
    G.init();
    sort(edge + 1, edge + 1 + m);
    for (int i = 1; i <= m; ++i) {
        int u = edge[i].u, v = edge[i].v, w = edge[i].w;
        int fu = find(u), fv = find(v);
        if (fu == fv)
            continue;
        pre[fu] = fv;
        edge[i].vis = 1;
        G.add(u, v, w);
    }
}

int fa[N][DEG], dis[N][DEG], deep[N];
void BFS() {
    queue<int> q;
    deep[1] = 0;
    fa[1][0] = 1;
    dis[1][0] = 0;
    q.push(1);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = 1; i < DEG; ++i) {
            fa[u][i] = fa[fa[u][i - 1]][i - 1];
            dis[u][i] = max(dis[u][i - 1], dis[fa[u][i - 1]][i - 1]);
        }
        erp(u) if (v != fa[u][0]) {
            deep[v] = deep[u] + 1;
            fa[v][0] = u;
            dis[v][0] = w;
            q.push(v);
        }
    }
}

int query(int u, int v) {
    if (u == v)
        return 0;
    if (deep[u] > deep[v])
        swap(u, v);
    int res = 0, hu = deep[u], hv = deep[v], tu = u, tv = v;
    for (int det = hv - hu, i = 0; det; det >>= 1, ++i) {
        if (det & 1) {
            res = max(res, dis[tv][i]);
            tv = fa[tv][i];
        }
    }
    if (tu == tv)
        return res;
    for (int i = DEG - 1; i >= 0; --i) {
        if (fa[tu][i] == fa[tv][i])
            continue;
        res = max(res, max(dis[tu][i], dis[tv][i]));
        tu = fa[tu][i];
        tv = fa[tv][i];
    }
    return max(res, max(dis[tu][0], dis[tv][0]));
}

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        for (int i = 1; i <= m; ++i) edge[i].scan();
        Kruskal();
        BFS();
        ll res = 0;
        for (int i = 1; i <= m; ++i)
            if (!edge[i].vis) {
                int Max = query(edge[i].u, edge[i].v);
                if (edge[i].w == Max)
                    res += Max;
            }
        printf("%lld\n", res);
    }
    return 0;
}
