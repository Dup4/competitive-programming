#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 10, mod = 1e4;
int n, k, f[N][N];

int main() {
    while (scanf("%d%d", &n, &k) != EOF) {
        memset(f, 0, sizeof f);
        f[0][0] = 1;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= k; ++j) (f[i - 1][j] += f[i - 1][j - 1]) %= mod;
            for (int j = 0; j <= k; ++j) {
                int l = j, r = j - min(j, i - 1);
                f[i][j] += (f[i - 1][l] - f[i - 1][r - 1] + mod) % mod;
                f[i][j] %= mod;
            }
        }
        printf("%d\n", f[n][k]);
    }
    return 0;
}
