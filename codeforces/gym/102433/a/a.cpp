#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using ll = long long;
using pLL = pair<ll, ll>;
const int N = 1e5 + 10;
int n, a[N], fa[N], sze[N];
ll res[N];

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

struct E {
    ll Sdis, Sval, S;
} f[N], g[N];

void dfs(int u) {
    f[u] = {0, 0, 0};
    sze[u] = 1;
    for (int i = G.h[u]; ~i; i = G.e[i].nx) {
        int v = G.e[i].to, w = G.e[i].w;
        if (v == fa[u])
            continue;
        fa[v] = u;
        dfs(v);
        sze[u] += sze[v];
        f[u].Sdis += f[v].Sdis + 1ll * sze[v] * w;
        f[u].Sval += f[v].Sval;
        f[u].S += f[v].S + f[v].Sval * w;
    }
    res[u] += 1ll * a[u] * f[u].Sdis + f[u].S;
    f[u].Sval += a[u];
}

void dfs1(int u) {
    for (int i = G.h[u]; ~i; i = G.e[i].nx) {
        int v = G.e[i].to, w = G.e[i].w;
        if (v == fa[u])
            continue;
        g[v].Sdis = g[u].Sdis + f[u].Sdis - f[v].Sdis - 1ll * sze[v] * w + 1ll * (n - sze[v]) * w;
        g[v].Sval = g[u].Sval + f[u].Sval - f[v].Sval;
        g[v].S = g[u].S + f[u].S - f[v].S - f[v].Sval * w + g[v].Sval * w;
        res[v] += 1ll * a[v] * g[v].Sdis + g[v].S;
        dfs1(v);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i), res[i] = 0;
    G.init(n);
    for (int i = 1, u, v, w; i < n; ++i) {
        scanf("%d%d%d", &u, &v, &w);
        G.addedge(u, v, w);
        G.addedge(v, u, w);
    }
    dfs(1);
    g[1] = {0, 0, 0};
    dfs1(1);
    for (int i = 1; i <= n; ++i) printf("%lld\n", res[i]);
    return 0;
}
