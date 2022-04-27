#include <bits/stdc++.h>
using namespace std;

#define db double
db x[10], y[10], u[10], v[10], X, Y, U, V, W;

struct GAUSS {
    const db eps = 1e-6;
#define N 20
    int n, w[N];
    db a[N][N], v[N];
    void init(int n) {
        this->n = n;
        memset(a, 0, sizeof a);
    }
    bool work() {
        for (int i = 1; i <= n; ++i) {
            int p = 0;
            db mx = 0;
            for (int j = 1; j <= n; ++j) {
                if (fabs(a[i][j]) - eps > mx) {
                    mx = fabs(a[i][j]);
                    p = j;
                }
            }
            if (!p) {
                return 0;
            }
            w[i] = p;
            for (int j = 1; j <= n; ++j) {
                if (i != j) {
                    db t = a[j][p] / a[i][p];
                    for (int k = 1; k <= n + 1; ++k) {
                        a[j][k] -= a[i][k] * t;
                    }
                }
            }
        }
        for (int i = 1; i <= n; ++i) v[w[i]] = a[i][n + 1] / a[i][w[i]];
        return 1;
    }
} gauss;

int main() {
    while (scanf("%lf%lf%lf%lf", x + 1, y + 1, u + 1, v + 1) != EOF) {
        for (int i = 2; i <= 4; ++i) scanf("%lf%lf%lf%lf", x + i, y + i, u + i, v + i);
        scanf("%lf%lf", &X, &Y);
        gauss.init(8);
        for (int i = 1; i <= 4; ++i) {
            gauss.a[i][1] = x[i];
            gauss.a[i][2] = y[i];
            gauss.a[i][3] = 1;
            gauss.a[i][7] = -x[i] * u[i];
            gauss.a[i][8] = -y[i] * u[i];
            gauss.a[i][9] = u[i];
        }
        for (int i = 1; i <= 4; ++i) {
            gauss.a[i + 4][4] = x[i];
            gauss.a[i + 4][5] = y[i];
            gauss.a[i + 4][6] = 1;
            gauss.a[i + 4][7] = -x[i] * v[i];
            gauss.a[i + 4][8] = -y[i] * v[i];
            gauss.a[i + 4][9] = v[i];
        }
        gauss.work();
        U = gauss.v[1] * X + gauss.v[2] * Y + gauss.v[3];
        V = gauss.v[4] * X + gauss.v[5] * Y + gauss.v[6];
        W = gauss.v[7] * X + gauss.v[8] * Y + 1;
        printf("%.6f %.6f\n", U / W, V / W);
    }
    return 0;
}
