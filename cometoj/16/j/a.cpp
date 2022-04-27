#include <bits/stdc++.h>
using namespace std;
typedef double db;
const int N = 5e2 + 10;
int n, f[N], g[N];
db x[N][2], y[N][2], z[N][2], nxY[N][2], nxZ[N][2];

db sqr(db x) {
    return x * x;
}
db gao() {
    int loop = 50000;
    db alpha = 1e-3;
    while (loop--) {
        for (int i = 1; i <= n; ++i) {
            nxY[f[i]][0] -= alpha * (2.0 * y[f[i]][0] - x[i][0] - z[g[i]][0]);
            nxY[f[i]][1] -= alpha * (2.0 * y[f[i]][1] - x[i][1] - z[g[i]][1]);
            nxZ[g[i]][0] -= alpha * (-y[f[i]][0] + z[g[i]][0]);
            nxZ[g[i]][1] -= alpha * (-y[f[i]][1] + z[g[i]][1]);
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j < 2; ++j) {
                y[i][j] = nxY[i][j];
                z[i][j] = nxZ[i][j];
            }
        }
    }
    db res = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < 2; ++j) {
            res += sqr(x[i][j] - y[f[i]][j]);
            res += sqr(y[f[i]][j] - z[g[i]][j]);
        }
    }
    return res;
}

int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; ++i) scanf("%lf%lf", x[i], x[i] + 1);
        for (int i = 1; i <= n; ++i) scanf("%d", f + i);
        for (int i = 1; i <= n; ++i) scanf("%d", g + i);
        printf("%.6f\n", gao());
    }
    return 0;
}
