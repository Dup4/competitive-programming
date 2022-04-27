#include <bits/stdc++.h>
using namespace std;
const int N = 5e2 + 10;
int n, m, a[N][N], f[N][N];
char g[N][N];

int main() {
    int _T;
    scanf("%d", &_T);
    while (_T--) {
        scanf("%d%d", &n, &m);
        memset(f, 0, sizeof f);
        for (int i = 1; i <= n; ++i) {
            scanf("%s", g[i] + 1);
            for (int j = 1; j <= m; ++j) {
                a[i][j] = g[i][j] - '0';
            }
        }
        int res = 0;
        for (int j = m; j >= 1; --j) {
            for (int i = n; i >= 1; --i) {
                f[i][j] += f[i + 1][j];
                int now = f[i][j] + f[i][j + 1];
                if ((now % 2) ^ a[i][j]) {
                    ++f[i][j];
                    ++res;
                }
            }
            for (int i = n; i >= 1; --i) f[i][j] += f[i][j + 1];
        }
        if (res % 2)
            puts("call");
        else
            puts("aoligei");
    }
    return 0;
}
