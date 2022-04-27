#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 5010
const int p = 1e9 + 7;
int n, m, k;
vector<vector<int> > G;
int vis[N], f[N][N], g[N];
void add(int &x, int y) {
    x += y;
    if (x >= p) {
        x -= p;
    }
}
void sub(int &x, int y) {
    x -= y;
    if (x < 0) {
        x += p;
    }
}

void DFS(int u, int fa) {
    for (int i = 0; i <= k; ++i) {
        f[u][i] = 0;
    }
    if (vis[u]) {
        f[u][0] = 1;
    }
    for (auto v : G[u])
        if (v != fa) {
            DFS(v, u);
            for (int i = 0; i <= k; ++i) {
                g[i] = f[u][i];
                if (i) {
                    add(g[i], f[v][i - 1]);
                }
            }
            for (int i = 1; i <= k; ++i) {
                add(f[v][i], f[v][i - 1]);
            }
            for (int i = 1; i <= k; ++i) {
                add(g[i], 1ll * f[u][i] * f[v][min(k - i, i - 1)] % p);
            }
            for (int i = k; i >= 1; --i) {
                sub(f[v][i], f[v][i - 1]);
            }
            for (int i = 1; i <= k; ++i) {
                add(f[u][i], f[u][i - 1]);
            }
            for (int i = 0; i <= k; ++i) {
                add(g[i + 1], 1ll * f[v][i] * f[u][min(k - i, i)] % p);
            }
            for (int i = 0; i <= k; ++i) {
                f[u][i] = g[i];
            }
        }
}

void init() {
    G.clear();
    G.resize(n + 1);
    memset(vis, 0, sizeof vis);
}
int main() {
    while (scanf("%d%d%d", &n, &m, &k) != EOF) {
        init();
        for (int i = 1, u, v; i < n; ++i) {
            scanf("%d%d", &u, &v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        for (int i = 1, x; i <= m; ++i) {
            scanf("%d", &x);
            vis[x] = 1;
        }
        DFS(1, 1);
        int res = 0;
        for (int i = 0; i <= k; ++i) {
            add(res, f[1][i]);
        }
        printf("%d\n", res);
    }
    return 0;
}
