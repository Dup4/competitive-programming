#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e4 + 10;
const int mod = 1e9 + 7;
int n;
struct Edge {
    int v, w, nx;
} e[N << 1];
int h[N];
inline void addedge(int u, int v, int w) {
    e[++*h] = {v, w, h[u]};
    h[u] = *h;
}
int vis[N], rt, sum, sze[N], f[N];
ll dis[N], res[5], cnt[5], tot[5];
void getrt(int u, int fa) {
    f[u] = 0, sze[u] = 1;
    for (int i = h[u]; i; i = e[i].nx) {
        int v = e[i].v;
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

void calc(int u, int fa) {
    for (int i = 0; i < 3; ++i) {
        int nx = (i + dis[u]) % 3;
        res[nx] += dis[u] * cnt[i] % mod + tot[i];
        res[nx] %= mod;
    }
    for (int i = h[u]; i; i = e[i].nx) {
        int v = e[i].v;
        if (v == fa || vis[v])
            continue;
        dis[v] = dis[u] + e[i].w;
        calc(v, u);
    }
}

void add(int u, int fa) {
    ++cnt[dis[u] % 3];
    tot[dis[u] % 3] += dis[u];
    tot[dis[u] % 3] %= mod;
    for (int i = h[u]; i; i = e[i].nx) {
        int v = e[i].v;
        if (v == fa || vis[v])
            continue;
        add(v, u);
    }
}

void gao(int u) {
    vis[u] = 1;
    memset(cnt, 0, sizeof cnt);
    memset(tot, 0, sizeof tot);
    ++cnt[0];
    for (int i = h[u]; i; i = e[i].nx) {
        int v = e[i].v;
        if (vis[v])
            continue;
        dis[v] = e[i].w;
        calc(v, u);
        add(v, u);
    }
    for (int i = h[u]; i; i = e[i].nx) {
        int v = e[i].v;
        if (vis[v])
            continue;
        sum = f[0] = sze[v];
        rt = 0;
        getrt(v, 0);
        gao(rt);
    }
}

int main() {
    while (scanf("%d", &n) != EOF) {
        memset(res, 0, sizeof res);
        for (int i = 0; i <= n; ++i) {
            h[i] = 0;
            vis[i] = 0;
        }
        for (int i = 1, u, v, w; i < n; ++i) {
            scanf("%d%d%d", &u, &v, &w);
            ++u, ++v;
            addedge(u, v, w);
            addedge(v, u, w);
        }
        sum = f[0] = n;
        rt = 0;
        getrt(1, 0);
        gao(rt);
        printf("%lld %lld %lld\n", (res[0] * 2) % mod, (res[1] * 2) % mod, (res[2] * 2) % mod);
    }
    return 0;
}
