#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int N = 5e3 + 10;
int n, fa[N];
ll res;
int f[N][N], g[N][N];
vector<vector<int> > G;

void DFS(int u) {
    f[u][0] = 1;
    for (int _ = 0, sze = (int)G[u].size(); _ < sze; ++_) {
        int v = G[u][_];
        if (v == fa[u])
            continue;
        fa[v] = u;
        DFS(v);
        for (int i = 1; i <= n; ++i) {
            res += g[u][i] * f[v][i - 1];
        }
        for (int i = 0; i <= n; ++i) {
            if (i) {
                g[u][i] += f[u][i] * f[v][i - 1];
                f[u][i] += f[v][i - 1];
            }
            g[u][i] += g[v][i + 1];
        }
    }
    res += g[u][0];
}

int main() {
    scanf("%d", &n);
    G.clear();
    G.resize(n + 1);
    memset(f, 0, sizeof(f[0]) * (n + 5));
    memset(g, 0, sizeof(g[0]) * (n + 5));
    for (int i = 1, u, v; i < n; ++i) {
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    res = 0;
    DFS(1);
    printf("%lld\n", res);
    return 0;
}
