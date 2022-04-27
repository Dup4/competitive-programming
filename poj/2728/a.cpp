#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
using namespace std;
#define db double
const int N = 1e3 + 10;
const db eps = 1e-8;
inline int sgn(db x) {
    if (fabs(x) < eps)
        return 0;
    return x > 0 ? 1 : -1;
}
int n, x[N], y[N], h[N];
db dis[N][N], cost[N][N], ans;
inline db getdis(int a, int b) {
    return sqrt((x[a] - x[b]) * (x[a] - x[b]) + (y[a] - y[b]) * (y[a] - y[b]));
}

struct Prime {
    bool vis[N];
    db val[N], w[N];
    db gao(db k) {
        db x = 0.0, y = 0.0;
        for (int i = 1; i <= n; ++i) {
            w[i] = cost[1][i] - dis[1][i] * k;
            val[i] = cost[1][i];
            vis[i] = 0;
        }
        vis[1] = 1;
        for (int o = 2; o <= n; ++o) {
            db mi = 1e9;
            int pos = 0;
            for (int i = 1; i <= n; ++i)
                if (!vis[i]) {
                    if (w[i] < mi) {
                        mi = w[i];
                        pos = i;
                    }
                }
            vis[pos] = 1;
            x += val[pos];
            y += val[pos] - w[pos];
            for (int i = 1; i <= n; ++i)
                if (!vis[i]) {
                    if (w[i] > cost[pos][i] - dis[pos][i] * k) {
                        w[i] = cost[pos][i] - dis[pos][i] * k;
                        val[i] = cost[pos][i];
                    }
                }
        }
        return x * k / y;
    }
} prime;

int main() {
    while (scanf("%d", &n), n) {
        db ma = -1e9, mi = 1e9;
        // cost / len
        for (int i = 1; i <= n; ++i) {
            scanf("%d%d%d", x + i, y + i, h + i);
        }
        for (int i = 1; i <= n; ++i) {
            dis[i][i] = cost[i][i] = 0;
            for (int j = i + 1; j <= n; ++j) {
                dis[i][j] = dis[j][i] = getdis(i, j);
                cost[i][j] = cost[j][i] = fabs(h[i] - h[j]);
                mi = min(mi, cost[i][j]);
                ma = max(ma, dis[i][j]);
            }
        }
        db L = mi / ma;
        while (1) {
            ans = prime.gao(L);
            if (sgn(ans - L) == 0)
                break;
            L = ans;
        }
        printf("%.3f\n", ans);
    }
    return 0;
}
