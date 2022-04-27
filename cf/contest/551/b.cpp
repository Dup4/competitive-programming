#include <bits/stdc++.h>
using namespace std;

#define N 110
int G[N][N];
int n, m, h;
int a[N], b[N];

int main() {
    while (scanf("%d%d%d", &n, &m, &h) != EOF) {
        for (int i = 1; i <= m; ++i) {
            scanf("%d", b + i);
        }
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                scanf("%d", &G[i][j]);
                if (G[i][j]) {
                    G[i][j] = min(a[i], b[j]);
                }
            }
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                printf("%d%c", G[i][j], " \n"[j == m]);
            }
        }
    }
    return 0;
}
