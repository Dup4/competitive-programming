#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
const int inf = ~0u >> 2;
const int MAX_N = 1010;
int d[MAX_N][MAX_N], di[MAX_N][MAX_N];
int rk[MAX_N][MAX_N];
int main() {
    int n, m, a, b, c;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        d[i][i] = 0;
        di[i][i] = 0;
        for (int j = i + 1; j <= n; j++) {
            di[i][j] = di[j][i] = inf;
            d[i][j] = d[j][i] = inf;
        }
    }
    for (int i = 0; i < m; i++) {
        scanf("%d%d%d", &a, &b, &c);
        d[a][b] = d[b][a] = c;
        di[a][b] = di[b][a] = c;
    }
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) rk[i][j] = j;
        for (int j = 1; j <= n; j++) {
            for (int k = j + 1; k <= n; k++) {
                if (d[i][rk[i][j]] > d[i][rk[i][k]]) {
                    swap(rk[i][j], rk[i][k]);
                }
            }
        }
    }
    int ans = inf;
    for (int u = 1; u <= n; u++) {
        for (int v = 1; v <= n; v++)
            if (u != v) {
                ans = min(ans, d[u][rk[u][n]] << 1);
                ans = min(ans, d[v][rk[v][n]] << 1);
                for (int cmp = n, i = n - 1; i >= 1; i--) {
                    if (d[v][rk[u][i]] > d[v][rk[u][cmp]]) {
                        ans = min(ans, d[u][rk[u][i]] + d[v][rk[u][cmp]] + di[u][v]);
                        cmp = i;
                    }
                }
            }
    }
    printf("%d\n", ans);
    //	printf("%lf\n",(double)ans/2);
    return 0;
}
