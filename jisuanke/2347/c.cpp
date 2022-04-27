#include <bits/stdc++.h>
using namespace std;

#define N 1010
#define INF 0x3f3f3f3f
int n, a[N], f[N][N];

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
        }
        memset(f, 0x3f, sizeof f);
        f[1][1] = -1;
        f[1][0] = a[1];
        int res = INF;
        for (int i = 2; i <= n; ++i) {
            if (f[i - 1][0] < a[i]) {
                f[i][0] = a[i];
            }
            for (int j = 0; j < i; ++j) {
                if (a[i - 1] < a[i]) {
                    f[i][j + 1] = min(f[i][j + 1], f[i - 1][j]);
                }
                if (f[i - 1][j] < a[i]) {
                    f[i][i - j] = min(f[i][i - j], a[i - 1]);
                }
            }
        }
        for (int i = 1; i < n; ++i) {
            if (f[n][i] != INF) {
                res = min(res, abs(i - n + i));
            }
        }
        if (res == INF) {
            res = -1;
        }
        printf("%d\n", res);
    }
    return 0;
}
