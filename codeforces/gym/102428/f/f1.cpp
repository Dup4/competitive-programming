#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define dbg(x...)                             \
    do {                                      \
        cout << "\033[32;1m" << #x << " -> "; \
        err(x);                               \
    } while (0)
void err() {
    cout << "\033[39;0m" << endl;
}
template <class T, class... Ts>
void err(const T& arg, const Ts&... args) {
    cout << arg << ' ';
    err(args...);
}

const int mod = 1e9 + 7;
const int N = 5e3 + 10;
int n, S, B;
ll f[N][N], g[N][N], h[N][N];

// f[i][j] 用了i个 最上面一层有j 个的方案数

int main() {
    scanf("%d%d", &S, &B);
    memset(f, 0, sizeof f);
    memset(g, 0, sizeof g);
    memset(h, 0, sizeof h);
    f[S][S] = 1;
    for (int i = S; i >= 1; --i) {
        g[S][i] = (g[S][i + 1] + f[S][i]) % mod;
        h[S][i] = (h[S][i + 1] + f[S][i] * i % mod) % mod;
    }
    for (int i = S + 1; i <= B; ++i) {
        for (int j = 1; j <= S; ++j) {
            f[i][j] = 1ll * (1 - j + mod) % mod * (g[i - j][j] - g[i - j][S + 1] + mod) % mod;
            f[i][j] = (f[i][j] + (h[i - j][j] - h[i - j][S + 1] + mod) % mod) % mod;
            //	if (f[i][j]) dbg(i, j, f[i][j]);
        }
        for (int j = S; j >= 1; --j) {
            g[i][j] = (g[i][j + 1] + f[i][j]) % mod;
            h[i][j] = (h[i][j + 1] + f[i][j] * j % mod) % mod;
        }
    }
    ll res = 0;
    for (int i = 1; i <= S; ++i) {
        res = (res + f[B][i]) % mod;
    }
    printf("%lld\n", res);
    return 0;
}
