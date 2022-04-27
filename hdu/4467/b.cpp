#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pII = pair<int, int>;
#define fi first
#define se second
const int N = 1e5 + 10;
int n, m, q, a[N], d[N], ee[N][3], big[N], S;
ll f[N][2], g[3];
struct Edge {
    int v, nx;
    ll w;
} e[N << 1];
int h[N];
inline void addedge(int u, int v, ll w) {
    e[++*h] = {v, h[u], w};
    h[u] = *h;
}
inline ll id(int u, int v) {
    return 1ll * u * n + v;
}
map<ll, ll> mp;
void up(int u, int vis) {
    if (big[u]) {
        g[a[u]] += f[u][0] * vis;
        g[a[u] + 1] += f[u][1] * vis;
    }
    for (int o = h[u]; o; o = e[o].nx) {
        int v = e[o].v;
        ll w = e[o].w;
        g[a[u] + a[v]] += w * vis;
        if (big[u] != big[v]) {
            f[v][a[u]] += w * vis;
        }
    }
}

int main() {
    int kase = 1;
    while (scanf("%d%d", &n, &m) != EOF) {
        S = sqrt(n);
        printf("Case %d:\n", kase++);
        for (int i = 0; i <= n; ++i) {
            d[i] = h[i] = 0;
            f[i][0] = f[i][1] = 0;
        }
        memset(g, 0, sizeof g);
        mp.clear();
        for (int i = 1; i <= n; ++i) scanf("%d", a + i);
        for (int i = 1; i <= m; ++i) {
            scanf("%d%d%d", ee[i], ee[i] + 1, ee[i] + 2);
            if (ee[i][0] > ee[i][1])
                swap(ee[i][0], ee[i][1]);
            ++d[ee[i][0]];
            ++d[ee[i][1]];
            mp[id(ee[i][0], ee[i][1])] += ee[i][2];
        }
        for (int i = 1; i <= n; ++i) {
            big[i] = (d[i] >= S);
        }
        for (int i = 1; i <= m; ++i) {
            int u = ee[i][0], v = ee[i][1];
            ll &w = mp[id(ee[i][0], ee[i][1])];
            if (!w)
                continue;
            if (big[u] == big[v]) {
                addedge(u, v, w);
                addedge(v, u, w);
            } else {
                if (big[u])
                    swap(u, v);
                addedge(u, v, w);
                f[v][a[u]] += w;
            }
            w = 0;
        }
        for (int u = 1; u <= n; ++u) {
            g[a[u]] += f[u][0];
            g[a[u] + 1] += f[u][1];
        }
        for (int u = 1; u <= n; ++u) {
            for (int o = h[u]; o; o = e[o].nx) {
                int v = e[o].v;
                ll w = e[o].w;
                if (v > u || big[u] != big[v])
                    continue;
                g[a[u] + a[v]] += w;
            }
        }
        //	for (int i = 1; i <= n; ++i) cout << i << " " << f[i][0] << " " << f[i][1] << endl;
        scanf("%d", &q);
        char op[10];
        int x, y;
        while (q--) {
            scanf("%s%d", op, &x);
            if (op[0] == 'A') {
                scanf("%d", &y);
                printf("%lld\n", g[x + y]);
            } else {
                up(x, -1);
                a[x] ^= 1;
                up(x, 1);
            }
        }
    }
    return 0;
}
