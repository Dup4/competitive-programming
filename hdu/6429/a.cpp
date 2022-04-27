#include <bits/stdc++.h>
using namespace std;

#define N 110
int f[N][N][N * N];
int n, m, p;

void init() {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            for (int k = 0; k <= m; ++k) {
                f[i][j][k] = 0;
            }
        }
    }
}
int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &p);
        m = n * (n - 1) / 2;
        init();
        f[1][1][0] = 1;
        for (int i = 2; i <= n; ++i) {
            for (int j = 1; j < i; ++j) {
                for (int k = 0; k <= m; ++k) {
                    (f[i][i][k] += f[i - 1][j][k]) %= p;
                }
            }
            for (int j = 1; j < i; ++j) {
                for (int k = 1; k < i; ++k) {
                    for (int o = 0; o <= m; ++o) {
                        (f[i][i][o] += (f[j][k][o])) %= p;
                        int nx = o - abs(j - k) + (i - k) + (i - j);
                        if (nx >= 0 && nx <= m) {
                            (f[i][k][nx] += f[j][k][o]) %= p;
                            (f[j][i][nx] += f[j][k][o]) %= p;
                        }
                    }
                }
            }
        }
        for (int j = 0; j <= m; ++j) {
            for (int i = 1; i <= n; ++i) {
                (f[n][i][j] += f[n][i - 1][j]) %= p;
            }
        }
        for (int i = 0; i <= (n * n - 1); ++i) {
            printf("%d%c", f[n][n][i], " \n"[i == (n * n - 1)]);
        }
    }
    return 0;
}
