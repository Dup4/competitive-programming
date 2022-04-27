#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define SZ(x) (int(x.size()))
const int N = 1e3 + 10, mod = 1e9 + 7;
int n, m, v[N], fac[N], inv[N], bit[N], fbit[N];
ll f[N][N];
char s[N];

ll qpow(ll base, ll n) {
    ll res = 1;
    while (n) {
        if (n & 1)
            res = res * base % mod;
        base = base * base % mod;
        n >>= 1;
    }
    return res;
}

ll C(int n, int m) {
    return 1ll * fac[n] * inv[m] % mod * inv[n - m] % mod;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    fac[0] = 1;
    for (int i = 1; i < N; ++i) fac[i] = 1ll * fac[i - 1] * i % mod;
    inv[N - 1] = qpow(fac[N - 1], mod - 2);
    for (int i = N - 1; i >= 1; --i) inv[i - 1] = 1ll * inv[i] * i % mod;
    bit[0] = 1;
    for (int i = 1; i < N; ++i) bit[i] = 1ll * bit[i - 1] * 26 % mod;
    fbit[0] = 1;
    fbit[1] = qpow(26, mod - 2);
    for (int i = 2; i < N; ++i) fbit[i] = 1ll * fbit[i - 1] * fbit[1] % mod;
    f[0][0] = 1;
    for (int i = 1; i < N; ++i) {
        for (int j = 0; j <= i; ++j) {
            if (!j) {
                f[i][j] += f[i - 1][0] + f[i - 1][1];
                f[i][j] %= mod;
            } else if (j < i) {
                f[i][j] += f[i - 1][j - 1] * 26 + f[i - 1][j + 1];
                f[i][j] %= mod;
            } else if (j == i) {
                f[i][j] += f[i - 1][j - 1] * 26 % mod;
                f[i][j] %= mod;
            }
        }
    }
    cin >> n >> m;
    vector<string> vec(n + 1);
    for (int i = 1; i <= n; ++i) cin >> vec[i] >> v[i];
    ll res = 0;
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            int len = SZ(vec[j]);
            if (i >= len) {
                res += f[m][i] * (i - len + 1) % mod * v[j] % mod * fbit[len] % mod;
                res %= mod;
            }
        }
    }
    printf("%lld\n", res);
    return 0;
}
