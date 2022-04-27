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
int n, S, B, f[N][N];

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

ll inv(ll x, ll mod) {
    return qpow(x, mod - 2);
}

int main() {
    scanf("%d%d", &S, &B);
    n = B;
    memset(f, 0, sizeof f);
    for (int i = 0; i <= n; ++i) f[i][0] = 1, f[1][i] = 1;
    for (int i = 2; i <= n; ++i) {
        for (int j = 1; j < i; ++j) {
            f[i][j] = f[j][j];
        }
        for (int j = i; j <= n; ++j) {
            f[i][j] = (f[i - 1][j] + f[i][j - i]) % mod;
        }
    }
    ll res = 0;
    for (int i = 1; i < S; ++i) {
        for (int j = 0; j <= B - S; ++j) {
            dbg(i, j, S - i, B - S - j, f[i][j], f[S - i][B - S - j]);
            res += 1ll * f[i][j] * f[S - i][B - S - j] % mod;
            res %= mod;
        }
    }
    cout << res << endl;
    res += 2ll * f[S][B - S] % mod;
    res %= mod;
    //	if ((B - S) % S == 0)
    res = (mod + res - S + 1) % mod;
    cout << res << endl;
    res = res * inv(2, mod) % mod;
    //	res += 2ll * f[S][B - S] % mod;
    // cout << res << endl;
    //	res = res * inv(S - 1, mod) % mod;
    //	if ((B - S) % S == 0) res = (mod + res - 1) % mod;
    //	cout << res << endl;
    //	res %= mod;
    //	cout << f[S][B - S] << endl;
    //	res = (mod + res - 1) % mod;
    printf("%lld\n", res);
    return 0;
}
