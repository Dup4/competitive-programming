#include <bits/stdc++.h>
using namespace std;

#define N 110
int h, w, n;
char G[N][N];

void File() {
    freopen("kotlin.in", "r", stdin);
    freopen("kotlin.out", "w", stdout);
}
int main() {
    File();
    while (scanf("%d%d%d", &h, &w, &n) != EOF) {
        int tot = ((w + 1) / 2) * ((h + 1) / 2);
        if (tot < n) {
            puts("Impossible");
            continue;
        }
        int x = (h + 1) / 2, y = (w + 1) / 2;
        if (x > y)
            swap(x, y);
        int a = 0, b = 0;
        bool flag = 0;
        for (int i = 1; i * i <= n; ++i)
            if (n % i == 0) {
                a = i, b = n / i;
                if (a > b)
                    swap(a, b);
                if (a <= x && b <= y) {
                    flag = 1;
                    break;
                }
            }
        if (!flag) {
            puts("Impossible");
            continue;
        }
        if (h > w) {
            swap(a, b);
        }
        memset(G, 0, sizeof G);
        for (int i = 1; (i + 1) / 2 <= a; i += 2) {
            for (int j = 1; (j + 1) / 2 <= b; ++j) {
                if ((j & 1) && n > 0) {
                    G[i][j] = '.';
                    --n;
                }
            }
        }
        if (n > 0) {
            puts("Impossible");
            continue;
        }
        for (int i = 1; i <= h; ++i) {
            for (int j = 1; j <= w; ++j) {
                if (G[i][j] != '.') {
                    G[i][j] = '#';
                }
            }
        }
        for (int i = 1; i <= h; ++i) {
            puts(G[i] + 1);
        }
    }
    return 0;
}
