#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
#define M 1100
int n, m, e[N][4], G[M][M];
ll C3[N];

ll solve(int dx, int dy) {
    memset(G, 0, sizeof G);
    for (int i = 1; i <= n; ++i) {
        int xl = e[i][0] + dx, yl = e[i][1] + dy, xr = e[i][2], yr = e[i][3];
        if (xl > xr || yl > yr) {
            continue;
        }
        ++G[xl][yl];
        --G[xl][yr + 1];
        --G[xr + 1][yl];
        ++G[xr + 1][yr + 1];
    }
    ll res = 0;
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= m; ++j) {
            G[i][j] += G[i - 1][j] + G[i][j - 1] - G[i - 1][j - 1];
            res += C3[G[i][j]];
        }
    }
    return res;
}

int main() {
    m = 1000;
    for (int i = 1; i <= 100000; ++i) {
        C3[i] = 1ll * i * (i - 1) * (i - 2) / 6;
    }
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j < 4; ++j) {
                scanf("%d", e[i] + j);
            }
        }
        printf("%lld\n", solve(0, 0) - solve(1, 0) - solve(0, 1) + solve(1, 1));
    }
    return 0;
}
