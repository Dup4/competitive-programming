#include <bits/stdc++.h>
using namespace std;

#define INF 0x3f3f3f3f
#define N 400010
#define D 100000
int n, a[N], b[N];
int f[N];

int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d%d", a + i, b + i);
        }
        memset(f, -0x3f, sizeof f);
        f[D] = 0;
        for (int i = 1; i <= n; ++i) {
            if (a[i] < 0) {
                for (int j = -D; j <= D; ++j) {
                    int nx = j + D - a[i];
                    if (f[nx] != INF) {
                        f[j + D] = max(f[j + D], f[nx] + b[i]);
                    }
                }
            } else {
                for (int j = D; j >= -D; --j) {
                    int nx = j + D - a[i];
                    if (f[nx] != INF) {
                        f[j + D] = max(f[j + D], f[nx] + b[i]);
                    }
                }
            }
        }
        int res = 0;
        for (int i = 0; i <= D; ++i) {
            if (f[i + D] >= 0) {
                res = max(res, i + f[i + D]);
            }
        }
        printf("%d\n", res);
    }
    return 0;
}
