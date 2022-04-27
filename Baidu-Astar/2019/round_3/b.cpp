#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>
#define fi first
#define se second
const int N = 1e3 + 10;
const int mod = 998244353;
inline void chadd(int &x, int y) {
    x += y;
    if (x >= mod)
        x -= mod;
}
int n, m, G[N][N], res[N][N];

void Floyd() {
    for (int k = 1; k <= n; ++k)
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j) {
                if (G[i][k] + G[k][j] < G[i][j]) {
                    G[i][j] = G[i][k] + G[k][j];
                    res[i][j] = k;
                }
            }
}

int main() {
    int _T;
    cin >> _T;
    while (_T--) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j) G[i][j] = 1e9, res[i][j] = 0;
        for (int i = 1; i <= n; ++i) G[i][i] = 0;
        for (int i = 1, u, v, w; i <= m; ++i) {
            scanf("%d%d%d", &u, &v, &w);
            G[u][v] = G[v][u] = w;
        }
        Floyd();
        int ans = 0;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j) chadd(ans, res[i][j]);
        printf("%d\n", ans);
    }
    return 0;
}
