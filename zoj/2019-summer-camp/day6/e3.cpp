#include <bits/stdc++.h>
using namespace std;

#define N 5010
int n, m, t, a[N], b[N], H[N << 1];
int f[N][N], g[N][2], que[2][N], top[2];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) f[i][j] = 0;
    for (int i = 1; i <= n; ++i) {
        scanf("%d", a + i);
    }
    scanf("%d", &m);
    for (int i = 1; i <= m; ++i) {
        scanf("%d", b + i);
    }
    int res = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            f[i][j] = max(f[i - 1][j], f[i][j - 1]);
            if (i == j) {
                f[i][j] = max(f[i][j], f[i - 1][j - 1] + 1);
            }
            res = max(res, f[i][j]);
        }
    }
    res = min(2, res);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
        }
    }
    printf("%d\n", res);
    return 0;
}
