#include <bits/stdc++.h>
using namespace std;

#define N 510
int n, a[N];
int f[N][N];

int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
        }
        memset(f, 0, sizeof f);
        int res = 0;
        for (int k = 1; k <= n; ++k) {
            for (int i = 0; i < k; ++i) {
                f[i][k] = max(f[i][k], a[k]);
                f[k][i] = max(f[k][i], a[k]);
                for (int j = 0; j < k; ++j)
                    if (i != j) {
                        if (a[k] >= a[i]) {
                            f[k][j] = max(f[k][j], f[i][j] + a[k]);
                            res = max(res, f[k][j]);
                        }
                        if (a[k] >= a[j]) {
                            f[i][k] = max(f[i][k], f[i][j] + a[k]);
                            res = max(res, f[i][k]);
                        }
                    }
            }
        }
        printf("%d\n", res);
    }
    return 0;
}
