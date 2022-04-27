#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 2e3 + 10;
const int mod = 1e9 + 9;
int n, k, f[N][N], C[N][N], a[N], b[N], c[N], fac[N];
inline void chadd(int &x, int y) {
    x += y;
    while (x >= mod) x -= mod;
    while (x < 0) x += mod;
}

int main() {
    C[0][0] = 1;
    for (int i = 1; i < N; ++i) {
        C[i][0] = 1;
        for (int j = 1; j <= i; ++j) {
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
        }
    }
    fac[0] = 1;
    for (int i = 1; i < N; ++i) fac[i] = 1ll * fac[i - 1] * i % mod;
    while (scanf("%d%d", &n, &k) != EOF) {
        for (int i = 1; i <= n; ++i) scanf("%d", a + i);
        for (int i = 1; i <= n; ++i) scanf("%d", b + i);
        if ((n + k) % 2 == 1) {
            puts("0");
            continue;
        }
        memset(f, 0, sizeof f);
        memset(c, 0, sizeof c);
        sort(a + 1, a + 1 + n);
        sort(b + 1, b + 1 + n);
        for (int i = 1; i <= n; ++i) c[i] = upper_bound(b + 1, b + 1 + n, a[i]) - b - 1;
        f[0][0] = 1;
        for (int i = 1; i <= n; ++i)
            for (int j = 0; j <= i; ++j) {
                f[i][j] = f[i - 1][j];
                if (j)
                    chadd(f[i][j], 1ll * f[i - 1][j - 1] * max(0, c[i] - j + 1) % mod);
            }
        for (int i = 1; i <= n; ++i) f[n][i] = (1ll * f[n][i] * fac[n - i] % mod);
        int K = (n + k) >> 1;
        int res = 0;
        for (int i = K, t = 1; i <= n; ++i, t *= -1) {
            chadd(res, (mod + 1ll * t * C[i][K] * f[n][i] % mod) % mod);
        }
        printf("%d\n", res);
    }
    return 0;
}
