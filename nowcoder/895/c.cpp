#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5 + 10;

int n, m;
char str[maxn];
char ans[maxn];

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &n, &m);
        scanf("%s", str + 1);
        if (str[1] != str[n + m]) {
            if (str[1] == 'U') {
                for (int i = 1; i <= m; ++i) {
                    putchar('R');
                }
                for (int i = 1; i <= n; ++i) {
                    putchar('U');
                }
                puts("");
                continue;
            } else {
                for (int i = 1; i <= n; ++i) {
                    putchar('U');
                }
                for (int i = 1; i <= m; ++i) {
                    putchar('R');
                }
                puts("");
                continue;
            }
        } else {
            if (str[1] == 'U') {
                int cnt = 0;
                int p = 0;
                for (int i = 1; i <= n + m; ++i) {
                    if (str[i] == 'R' && str[i + 1] == 'R') {
                        ++cnt;
                        p = 1;
                        break;
                    } else if (str[i] == 'R')
                        ++cnt;
                }
                if (p == 0)
                    puts("impossible");
                else {
                    for (int i = 1; i <= cnt; ++i) printf("R");
                    for (int i = 1; i <= n; ++i) printf("U");
                    for (int i = cnt + 1; i <= m; ++i) printf("R");
                    printf("\n");
                }
            } else {
                int cnt = 0;
                int p = 0;
                for (int i = 1; i <= n + m; ++i) {
                    if (str[i] == 'U' && str[i + 1] == 'U') {
                        ++cnt;
                        p = 1;
                        break;
                    } else if (str[i] == 'U')
                        ++cnt;
                }
                if (p == 0)
                    puts("impossible");
                else {
                    for (int i = 1; i <= cnt; ++i) printf("U");
                    for (int i = 1; i <= m; ++i) printf("R");
                    for (int i = cnt + 1; i <= n; ++i) printf("U");
                    printf("\n");
                }
            }
        }
    }
    return 0;
}
