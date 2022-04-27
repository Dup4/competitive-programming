#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
#define INF 0x3f3f3f3f
int n, k, c[N];
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

int vis[N];
int sum, root, sze[N], f[N];
void getroot(int u, int fa) {
    f[u] = 0, sze[u] = 1;
    erp(u) if (v != fa && !vis[v]) {
        getroot(v, u);
        sze[u] += sze[v];
        f[u] = max(f[u], sze[v]);
    }
    f[u] = max(f[u], sum - sze[u]);
    if (f[u] < f[root])
        root = u;
}

int dist[N], res, t[3020];
void getdeep(int u, int fa) {
    //	cout << dist[u] << " " << (2019 - dist[u] % 2019) % 2019 << endl;
    res += t[(2019 - dist[u] % 2019) % 2019];
    erp(u) if (v != fa && !vis[v]) {
        dist[v] = dist[u] + w;
        getdeep(v, u);
    }
}

void add(int u, int fa, int f) {
    t[dist[u] % 2019] += f;
    erp(u) if (v != fa && !vis[v]) add(v, u, f);
}

void solve(int u) {
    vis[u] = 1;
    t[0] = 1;
    dist[u] = 0;
    erp(u) if (!vis[v]) {
        dist[v] = dist[u] + w;
        getdeep(v, u);
        add(v, u, 1);
    }
    erp(u) if (!vis[v]) add(v, u, -1);
    erp(u) if (!vis[v]) {
        sum = f[0] = sze[v];
        root = 0;
        getroot(v, 0);
        solve(root);
    }
}

int main() {
    while (scanf("%d", &n) != EOF) {
        memset(t, 0, sizeof t);
        memset(vis, 0, sizeof(vis[0]) * (n + 10));
        G.init();
        for (int i = 1, u, v, w; i < n; ++i) {
            scanf("%d%d%d", &u, &v, &w);
            G.add(u, v, w);
        }
        res = 0;
        sum = f[0] = n;
        root = 0;
        getroot(1, 0);
        solve(root);
        printf("%d\n", res);
    }
}
