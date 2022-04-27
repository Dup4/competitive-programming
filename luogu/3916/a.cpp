#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
vector<vector<int>> G;
int n, m, f[N], vis[N];
void dfs(int u) {
    vis[u] = 1;
    for (auto &v : G[u])
        if (!vis[v]) {
            f[v] = max(f[v], f[u]);
            dfs(v);
        }
}

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        for (int i = 1; i <= n; ++i) f[i] = i, vis[i] = 0;
        G.clear();
        G.resize(n + 1);
        for (int i = 1, u, v; i <= m; ++i) {
            scanf("%d%d", &u, &v);
            G[v].push_back(u);
        }
        for (int i = n; i >= 1; --i) {
            if (f[i] == i)
                dfs(i);
        }
        for (int i = 1; i <= n; ++i) printf("%d%c", f[i], " \n"[i == n]);
    }
    return 0;
}
