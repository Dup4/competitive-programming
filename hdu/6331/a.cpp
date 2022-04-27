#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 210;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
int t, n, m, q;
ll G[N][55][55], dp[N][55][55];

// G[i][j][k] 经过i条边, j -> k 的最短路
// dp[i][j][k] 经过i*100条边, j -> k的最短路

void Floyd() {
    for (int l = 2; l <= 200; ++l)
        for (int k = 1; k <= n; ++k)
            for (int i = 1; i <= n; ++i)
                for (int j = 1; j <= n; ++j) G[l][i][j] = min(G[l][i][j], G[l - 1][i][k] + G[1][k][j]);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            for (int l = 199; l >= 0; --l) G[l][i][j] = min(G[l][i][j], G[l + 1][i][j]);  // at least K roads;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) dp[1][i][j] = G[100][i][j];
    for (int l = 2; l <= 100; ++l)
        for (int k = 1; k <= n; ++k)
            for (int i = 1; i <= n; ++i)
                for (int j = 1; j <= n; ++j) dp[l][i][j] = min(dp[l][i][j], dp[l - 1][i][k] + dp[1][k][j]);
}

int main() {
    int _T;
    scanf("%d", &_T);
    while (_T--) {
        scanf("%d%d", &n, &m);
        memset(G, 0x3f, sizeof G);
        memset(dp, 0x3f, sizeof dp);
        for (int i = 1, u, v, w; i <= m; ++i) {
            scanf("%d%d%d", &u, &v, &w);
            G[1][u][v] = min(G[1][u][v], 1ll * w);
        }
        Floyd();
        scanf("%d", &q);
        for (int i = 1, u, v, k; i <= q; ++i) {
            scanf("%d%d%d", &u, &v, &k);
            int unit = k / 100, remind = k - unit * 100;
            ll ans = INFLL;
            if (k <= 100)
                ans = G[k][u][v];
            else {
                for (int j = 1; j <= n; ++j) ans = min(ans, dp[unit][u][j] + G[remind][j][v]);
            }
            if (k > 100 && remind == 0)
                ans = min(ans, dp[unit][u][v]);
            printf("%lld\n", ans >= INFLL ? -1 : ans);
        }
    }
    return 0;
}
