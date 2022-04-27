#include <bits/stdc++.h>
using namespace std;

#define N 1010
int n, m, h[N], vis[N];

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        memset(vis, 0, sizeof vis);
        for (int i = 1; i <= n; ++i) scanf("%d", h + i);
        int res = 1;
        for (int i = 1, x; i <= m; ++i) {
            scanf("%d", &x);
            for (int j = 1; j <= n; ++j) {
                if (vis[j] == 0 && h[j] <= x) {
                    vis[j] = 1;
                    if (j > 1 && j < n) {
                        if (vis[j - 1] == 0 && vis[j + 1] == 0)
                            ++res;
                        else if (vis[j - 1] && vis[j + 1])
                            --res;
                    } else if (j > 1) {
                        if (vis[j - 1] == 1)
                            --res;
                    } else if (j < n) {
                        if (vis[j + 1] == 1)
                            --res;
                    }
                }
            }
            printf("%d\n", res);
        }
    }
    return 0;
}
