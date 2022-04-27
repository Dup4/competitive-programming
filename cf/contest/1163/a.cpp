#include <bits/stdc++.h>
using namespace std;
int vis[1100];
int n, m;
int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        if (m >= (n + 1) / 2) {
            printf("%d\n", n - m);
        } else {
            if (m == 0) {
                puts("1");
                continue;
            }
            memset(vis, 0, sizeof vis);
            for (int i = 1; i <= n && m > 0; i += 2) {
                --m;
                vis[i] = 1;
            }
            int res = 1;
            for (int i = 2; i <= n; ++i) {
                if (vis[i] == 1) {
                    ++res;
                }
            }
            printf("%d\n", res);
        }
    }
    return 0;
}
