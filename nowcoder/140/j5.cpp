#include <bits/stdc++.h>
using namespace std;

#define N 4000010
#define y1 y_1
int x1[N], y1[N], x2[N], y2[N], k[N];
int n, m, q;
int a[N], b[N], c[N];
bool die[N];
int id(int x, int y) {
    return (x - 1) * (m + 2) + y;
}
void up(int *f, int x1, int y1, int x2, int y2, int v) {
    f[id(x1, y1)] += v;
    f[id(x2 + 1, y2 + 1)] += v;
    f[id(x1, y2 + 1)] -= v;
    f[id(x2 + 1, y1)] -= v;
}
void work(int *f) {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            f[id(i, j)] += f[id(i - 1, j)] + f[id(i, j - 1)] - f[id(i - 1, j - 1)];
        }
    }
}

int main() {
    while (scanf("%d%d%d", &n, &m, &q) != EOF) {
        memset(b, 0, sizeof b);
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                scanf("%d", &a[id(i, j)]);
            }
        }
        for (int i = 1; i <= q; ++i) {
            scanf("%d%d%d%d%d", x1 + i, y1 + i, x2 + i, y2 + i, k + i);
            up(b, x1[i], y1[i], x2[i], y2[i], 1);
        }
        work(b);
        for (int i = 15; i >= 0; --i) {
            for (int _i = 1; _i <= n; ++_i) {
                for (int _j = 1; _j <= m; ++_j) {
                    c[id(_i, _j)] = 0;
                }
            }
            for (int j = 1; j <= q; ++j) {
                if (k[j] >> i & 1) {
                    up(c, x1[j], y1[j], x2[j], y2[j], 1);
                }
            }
            work(c);
            for (int _i = 1; _i <= n; ++_i) {
                for (int _j = 1; _j <= m; ++_j) {
                    if (a[id(_i, _j)] >> i & 1) {
                        if (b[id(_i, _j)] != c[id(_i, _j)]) {
                            die[id(_i, _j)] = 1;
                        }
                    } else if (c[id(_i, _j)]) {
                        die[id(_i, _j)] = 1;
                    }
                }
            }
        }
        int res = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                res += die[id(i, j)];
            }
        }
        printf("%d\n", res);
    }
    return 0;
}
