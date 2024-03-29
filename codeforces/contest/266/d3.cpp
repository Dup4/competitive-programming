#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int N = 1010;
int n, m;
int d[N][N], dis[N][N], rk[N][N];
int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        for (int i = 1; i <= n; i++) {
            d[i][i] = dis[i][i] = 0;
            for (int j = i + 1; j <= n; ++j) {
                dis[i][j] = dis[j][i] = INF;
                d[i][j] = d[j][i] = INF;
            }
        }
        for (int i = 1, u, v, w; i <= m; ++i) {
            scanf("%d%d%d", &u, &v, &w);
            d[u][v] = d[v][u] = min(d[u][v], w);
            dis[u][v] = dis[v][u] = d[u][v];
        }
        for (int k = 1; k <= n; ++k) {
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= n; ++j) {
                    dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
                }
            }
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) rk[i][j] = j;
            for (int j = 1; j <= n; ++j) {
                for (int k = j + 1; k <= n; ++k) {
                    if (dis[i][rk[i][j]] > dis[i][rk[i][k]]) {
                        swap(rk[i][j], rk[i][k]);
                    }
                }
            }
        }
        int ans = INF;
        for (int u = 1; u <= n; ++u) {
            for (int v = 1; v <= n; ++v)
                if (u != v) {
                    ans = min(ans, dis[u][rk[u][n]] << 1);
                    ans = min(ans, dis[v][rk[v][n]] << 1);
                    for (int cmp = n, i = n - 1; i >= 1; --i) {
                        if (dis[v][rk[u][i]] > dis[v][rk[u][cmp]]) {
                            ans = min(ans, dis[u][rk[u][i]] + dis[v][rk[u][cmp]] + d[u][v]);
                            cmp = i;
                        }
                    }
                }
        }
        printf("%lf\n", (double)ans / 2);
    }
    return 0;
}
