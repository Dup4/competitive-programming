#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>
#define fi first
#define se second
const int N = 1e3 + 10;
int n, m, res, dis[N], used[N], vis[N], rt;
vector<vector<pii>> G;
void DFS(int u) {
    used[u] = 1;
    for (auto &it : G[u]) {
        int v = it.fi, w = it.se;
        if (used[v])
            continue;
        if (vis[v] == 0 || dis[v] < dis[u] + w) {
            vis[v] = 1;
            dis[v] = dis[u] + w;
            res = max(res, dis[v]);
            DFS(v);
        }
    }
    used[u] = 0;
}
int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        G.clear();
        G.resize(n + 1);
        for (int i = 1, u, v, w; i <= m; ++i) {
            scanf("%d%d%d", &u, &v, &w);
            G[u].emplace_back(v, w);
        }
        res = 0;
        for (int i = 1; i <= n; ++i) {
            memset(used, 0, sizeof used);
            memset(dis, 0, sizeof dis);
            memset(vis, 0, sizeof vis);
            dis[i] = 0;
            used[i] = 1;
            rt = i;
            DFS(i);
        }
        printf("%d\n", res);
    }
    return 0;
}
