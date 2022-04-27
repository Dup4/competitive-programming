#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 200010
int n;
vector<vector<int>> G;
int fa[N], sze[N];
ll f[N], g[N], res;
void DFS(int u) {
    sze[u] = 1;
    f[u] = 0;
    for (auto v : G[u])
        if (v != fa[u]) {
            fa[v] = u;
            DFS(v);
            sze[u] += sze[v];
            f[u] += f[v];
        }
    f[u] += sze[u];
}

void DFS2(int u) {
    if (u == 1) {
        g[u] = 0;
    } else {
        g[u] = g[fa[u]] + f[fa[u]] - f[u] - sze[u] + n - sze[fa[u]];
        res = max(res, f[u] + g[u] - sze[u] + n);
    }
    for (auto v : G[u])
        if (v != fa[u]) {
            DFS2(v);
        }
}

int main() {
    while (scanf("%d", &n) != EOF) {
        G.clear();
        G.resize(n + 1);
        for (int i = 1, u, v; i < n; ++i) {
            scanf("%d%d", &u, &v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        DFS(1);
        res = f[1];
        DFS2(1);
        printf("%lld\n", res);
    }
    return 0;
}
