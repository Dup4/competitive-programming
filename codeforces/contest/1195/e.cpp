#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 3010
int n, m, a, b;
ll g[N * N], x, y, z;
int B[N][N], l[N], r[N], que[N], L, R;

int get(int x, int y) {
    return (x - 1) * m + y - 1;
}

int main() {
    while (scanf("%d%d%d%d", &n, &m, &a, &b) != EOF) {
        L = 1, R = 0;
        for (int i = 1; i <= n; ++i) l[i] = 1, r[i] = 0;
        scanf("%lld%lld%lld%lld", g, &x, &y, &z);
        for (int i = 1; i <= n * m; ++i) g[i] = (g[i - 1] * x + y) % z;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j < b; ++j) {
                while (l[i] <= r[i] && g[get(i, j)] < g[B[i][r[i]]]) {
                    --r[i];
                }
                B[i][++r[i]] = get(i, j);
            }
        }
        ll res = 0;
        for (int i = 1; i <= a; ++i) {
            while (L <= R && g[B[i][l[i]]] < g[que[R]]) --R;
            que[++R] = B[i][l[i]];
        }
        for (int j = b; j <= m; ++j) {
            for (int i = 1; i <= n; ++i) {
                while (l[i] <= r[i] && abs(B[i][l[i]] - get(i, j)) >= b) ++l[i];
                while (l[i] <= r[i] && g[get(i, j)] < g[B[i][r[i]]]) --r[i];
                B[i][++r[i]] = get(i, j);
            }
            L = 1, R = 0;
            for (int i = 1; i < a; ++i) {
                while (L <= R && g[B[i][l[i]]] < g[que[R]]) --R;
                que[++R] = B[i][l[i]];
            }
            for (int i = a; i <= n; ++i) {
                while (L <= R && abs(que[L] - get(i, j)) >= (a - 1) * m + b) ++L;
                while (L <= R && g[B[i][l[i]]] < g[que[R]]) --R;
                que[++R] = B[i][l[i]];
                res += g[que[L]];
            }
        }
        printf("%lld\n", res);
    }
    return 0;
}
