#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 10, M = 25;
int n, q, a[N], f[N], g[N];

struct RMQ {
    int Max[N][M];
    int mm[N];
    void init(int n, int *b) {
        mm[0] = -1;
        for (int i = 1; i <= n; ++i) {
            mm[i] = ((i & (i - 1)) == 0) ? mm[i - 1] + 1 : mm[i - 1];
            Max[i][0] = b[i];
        }
        for (int j = 1; j <= mm[n]; ++j) {
            for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
                Max[i][j] = max(Max[i][j - 1], Max[i + (1 << (j - 1))][j - 1]);
            }
        }
    }
    int queryMax(int x, int y) {
        int k = mm[y - x + 1];
        return max(Max[x][k], Max[y - (1 << k) + 1][k]);
    }
} rmqf, rmqg;

int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; ++i) scanf("%d", a + i);
        f[0] = 0;
        for (int i = 1; i <= n; ++i) {
            if (a[i] == 0)
                ++f[i];
            else
                --f[i];
            f[i] += f[i - 1];
        }
        g[n + 1] = 0;
        for (int i = n; i >= 1; --i) {
            if (a[i] == 1)
                ++g[i];
            else
                --g[i];
            g[i] += g[i + 1];
        }
        rmqf.init(n, f);
        rmqg.init(n, g);
        scanf("%d", &q);
        int l, r;
        while (q--) {
            scanf("%d%d", &l, &r);
            int remind = rmqf.queryMax(l, r) - f[l - 1] + rmqg.queryMax(l, r) - g[r + 1];
            printf("%d\n", (r - l + 1 - remind) / 2);
        }
    }
    return 0;
}
