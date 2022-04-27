#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pII = pair<int, int>;
#define fi first
#define se second
const int N = 1e5 + 10, S = 300;
int n, m, q, e[N][3], d[N], W[N], big[N], bigp[N], vis[N];
ll f[N][2], g[2], *h;  // 0 + 1 -
vector<vector<pII>> G;

int main() {
    bool empty = 0;
    while (scanf("%d%d%d", &n, &m, &q) != EOF) {
        if (empty)
            puts("");
        empty = 1;
        for (int i = 0; i <= n; ++i) {
            d[i] = big[i] = vis[i] = 0;
            f[i][0] = f[i][1] = 0;
        }
        *bigp = 0;
        g[0] = g[1] = 0;
        G.clear();
        G.resize(n + 1);
        for (int i = 1; i <= m; ++i) {
            scanf("%d%d%d", e[i], e[i] + 1, e[i] + 2);
            ++d[e[i][0]];
            ++d[e[i][1]];
        }
        for (int i = 1; i <= n; ++i) {
            if (d[i] >= S)
                bigp[++*bigp] = i, big[i] = 1;
        }
        for (int i = 1; i <= m; ++i) {
            int u = e[i][0], v = e[i][1], w = e[i][2];
            if (w == 0)
                continue;
            W[i] = w;
            if (big[u] == big[v]) {
                G[u].emplace_back(v, i);
                G[v].emplace_back(u, i);
            } else {
                if (big[u])
                    swap(u, v);
                G[u].emplace_back(v, i);
                if (w <= 0)
                    f[v][1] += abs(w);
                else
                    f[v][0] += abs(w);
            }
        }
        for (int u = 1; u <= n; ++u) {
            for (auto &it : G[u]) {
                int v = it.fi, &w = W[it.se];
                if (v > u || big[u] != big[v])
                    continue;
                if (w < 0)
                    g[1] += abs(w);
                else
                    g[0] += abs(w);
            }
        }
        char op[10];
        int u;
        while (q--) {
            scanf("%s", op);
            if (op[0] == 'Q') {
                scanf("%s", op);
                ll res = 0;
                if (op[0] == 'A' || op[0] == '+')
                    res += g[0];
                if (op[0] == 'A' || op[0] == '-')
                    res -= g[1];
                for (int i = 1; i <= *bigp; ++i) {
                    int u = bigp[i];
                    if (op[0] == 'A' || op[0] == '+')
                        res += f[u][0];
                    if (op[0] == 'A' || op[0] == '-')
                        res -= f[u][1];
                }
                printf("%lld\n", res);
            } else {
                scanf("%d", &u);
                if (big[u])
                    swap(f[u][0], f[u][1]);
                vis[u] ^= 1;
                for (auto &it : G[u]) {
                    int v = it.fi, &w = W[it.se];
                    if (big[u] == big[v])
                        h = g;
                    else
                        h = f[v];
                    int p = vis[u] ^ vis[v] ^ (w > 0);
                    h[p] -= abs(w);
                    h[p ^ 1] += abs(w);
                }
            }
        }
    }
    return 0;
}
