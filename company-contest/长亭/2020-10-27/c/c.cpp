#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(x) x.begin(), x.end()
#define SZ(x) (int(x.size()))

const int N = 5e2 + 10;
const int INF = 0x3f3f3f3f;
int n, k, m, id[N];
int f[N][N], g[1 << 12][12];

void floyd() {
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
            }
        }
    }
}

void chmin(int &x, int y) { x = min(x, y); }

int gao() {
    *id = 1;
    memset(g, 0x3f, sizeof g);
    g[1][0] = 0;
    for (int s = 1; s < 1 << (k + 1); ++s) {
        for (int j = 0; j < k + 1; ++j) if (((s >> j) & 1) && g[s][j] != INF) {
            for (int o = 0; o < k + 1; ++o) if (!((s >> o) & 1)){
                chmin(g[s | (1 << o)][o], g[s][j] + f[id[j]][id[o]]);
            }
        }
    }
    int res = INF;
    for (int i = 1; i <= k; ++i) {
        chmin(res, g[(1 << (k + 1)) - 1][i]);
    }
    return res;
}

int main() {
    int _T; scanf("%d", &_T);
    while (_T--) {
        memset(f, 0x3f, sizeof f);
        scanf("%d %d", &n, &k);
        for (int i = 1; i <= k; ++i) scanf("%d", id + i);
        scanf("%d", &m);
        for (int i = 1, u, v; i <= m; ++i) {
            scanf("%d %d", &u, &v);
            f[u][v] = f[v][u] = 1;
        }
        floyd();
        int res = gao();   
        if (res == INF) res = -1;
        printf("%d\n", res);
    }
    return 0;
}