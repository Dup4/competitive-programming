#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
const int M = 1e6 + 10;
const int INF = 0x3f3f3f3f;
int n, k;

struct Graph {
    struct E {
        int to, nx, w;
    } e[N << 1];
    int h[N], cnt;
    void init(int n) {
        for (int i = 0; i <= n; ++i) h[i] = -1;
        cnt = -1;
    }
    void addedge(int u, int v, int w = 0) {
        e[++cnt] = {v, h[u], w};
        h[u] = cnt;
    }
} G;

namespace DCTree {
int sum, rt, vis[N];
int sze[N], f[N];
int dist[N], deep[N], t[M], res;
void getrt(int u, int fa) {
    f[u] = 0, sze[u] = 1;
    for (int i = G.h[u]; ~i; i = G.e[i].nx) {
        int v = G.e[i].to;
        if (v == fa || vis[v])
            continue;
        getrt(v, u);
        sze[u] += sze[v];
        f[u] = max(f[u], sze[v]);
    }
    f[u] = max(f[u], sum - sze[u]);
    if (f[u] < f[rt])
        rt = u;
}
void getdeep(int u, int fa) {
    if (dist[u] <= k)
        res = min(res, deep[u] + t[k - dist[u]]);
    for (int i = G.h[u]; ~i; i = G.e[i].nx) {
        int v = G.e[i].to, w = G.e[i].w;
        if (v == fa || vis[v])
            continue;
        dist[v] = dist[u] + w;
        deep[v] = deep[u] + 1;
        getdeep(v, u);
    }
}
void add(int u, int fa, int opt) {
    if (dist[u] <= k) {
        if (opt)
            t[dist[u]] = min(t[dist[u]], deep[u]);
        else
            t[dist[u]] = INF;
    }
    for (int i = G.h[u]; ~i; i = G.e[i].nx) {
        int v = G.e[i].to;
        if (v == fa || vis[v])
            continue;
        add(v, u, opt);
    }
}
void solve(int u) {
    vis[u] = 1;
    t[0] = 0;
    for (int i = G.h[u]; ~i; i = G.e[i].nx) {
        int v = G.e[i].to, w = G.e[i].w;
        if (vis[v])
            continue;
        deep[v] = 1, dist[v] = w;
        getdeep(v, u);
        add(v, u, 1);
    }
    for (int i = G.h[u]; ~i; i = G.e[i].nx) {
        int v = G.e[i].to;
        if (vis[v])
            continue;
        add(v, u, 0);
    }
    for (int i = G.h[u]; ~i; i = G.e[i].nx) {
        int v = G.e[i].to;
        if (vis[v])
            continue;
        sum = f[0] = sze[v];
        rt = 0;
        getrt(v, 0);
        solve(rt);
    }
}
int gao() {
    res = INF;
    memset(vis, 0, sizeof vis);
    memset(t, 0x3f, sizeof t);
    sum = f[0] = n;
    rt = 0;
    getrt(1, 0);
    solve(rt);
    return res == INF ? -1 : res;
}
};  // namespace DCTree

int main() {
    while (scanf("%d%d", &n, &k) != EOF) {
        G.init(n);
        for (int i = 1, u, v, w; i < n; ++i) {
            scanf("%d%d%d", &u, &v, &w);
            ++u, ++v;
            G.addedge(u, v, w);
            G.addedge(v, u, w);
        }
        printf("%d\n", DCTree::gao());
    }
    return 0;
}
