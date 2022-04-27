#include <bits/stdc++.h>
using namespace std;
using pII = pair<int, int>;
#define fi first
#define se second
const int N = 3e2 + 10, INF = 0x3f3f3f3f;
int n, m;
vector<vector<pII>> G;
int g[N][N];
int dis[N], vis[N], Insta[N], res;
void dfs(int u, int pre) {
    vis[u] = 1;
    Insta[u] = 1;
    for (auto &it : G[u]) {
        int v = it.fi, w = it.se;
        if (v == pre)
            continue;
        if (Insta[v]) {
            res = min(res, w + dis[u] - dis[v]);
        }
        if (!vis[v]) {
            dis[v] = dis[u] + w;
            dfs(v, u);
        }
    }
    Insta[u] = 0;
}

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        G.clear();
        G.resize(n + 1);
        memset(g, 0x3f, sizeof g);
        for (int i = 1; i <= n; ++i) dis[i] = vis[i] = Insta[i] = 0;
        for (int i = 1, u, v, w; i <= m; ++i) {
            scanf("%d%d%d", &u, &v, &w);
            g[u][v] = g[v][u] = min(g[u][v], w);
        }
        for (int u = 1; u <= n; ++u) {
            for (int v = 1; v <= n; ++v) {
                if (u == v)
                    continue;
                if (g[u][v] != INF) {
                    G[u].push_back(pII(v, g[u][v]));
                }
            }
        }
        res = INF;
        //注意图不连通的情况
        for (int i = 1; i <= n; ++i)
            if (!vis[i]) {
                dis[i] = 0;
                dfs(i, i);
            }
        if (res == INF)
            puts("It's impossible.");
        else
            printf("%d\n", res);
    }
    return 0;
}
