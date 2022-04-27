#include <bits/stdc++.h>
using namespace std;

#define N 10010
bitset<N> b[110], now;
int a[N];

int main() {
    int m, n;
    while (scanf("%d%d", &m, &n) != EOF) {
        bool flag = 1;
        for (int i = 1; i <= m; ++i) {
            b[i].reset();
            now.reset();
            memset(a, 0, sizeof a);
            int k;
            scanf("%d", &k);
            for (int j = 1, x; j <= k; ++j) {
                scanf("%d", &x);
                a[x] = 1;
            }
            for (int j = 1; j <= n; ++j) {
                if (a[j] == 1) {
                    b[i][j] = 1;
                } else {
                    now[j] = 1;
                }
            }
            for (int j = 1; j < i; ++j) {
                bool F = 1;
                for (int k = 1; k <= n; ++k) {
                    if (b[j][k] == 1 && now[k] == 0) {
                        F = 0;
                        break;
                    }
                }
                if (F) {
                    flag = 0;
                }
            }
        }
        puts(flag ? "possible" : "impossible");
    }
    return 0;
}
