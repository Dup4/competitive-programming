#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 5e5 + 10;
const int M = 1e5 + 10;
const ll mod = 1e9 + 7;
const ll inv2 = 5e8 + 4;
ll n, k, k2, d[N], inv6;
char s[N];
int pri[N], check[N], mu[N];
void sieve() {
    memset(check, 0, sizeof check);
    *pri = 0;
    mu[1] = 1;
    for (int i = 2; i < N; ++i) {
        if (!check[i]) {
            pri[++*pri] = i;
            mu[i] = -1;
        }
        for (int j = 1; j <= *pri; ++j) {
            if (1ll * i * pri[j] >= N)
                break;
            check[i * pri[j]] = 1;
            if (i % pri[j] == 0) {
                mu[i * pri[j]] = 0;
                break;
            } else {
                mu[i * pri[j]] = -mu[i];
            }
        }
    }
    memset(d, 0, sizeof d);
    for (int i = 1; i < N; ++i)
        for (int j = i; j < N; j += i) d[j] = (d[j] + 1ll * i * i % mod * mu[j / i] % mod) % mod;
    for (int i = 1; i < N; ++i) d[i] = (d[i] + d[i - 1]) % mod;
}
inline ll qpow(ll base, ll n) {
    ll res = 1;
    while (n) {
        if (n & 1)
            res = res * base % mod;
        base = base * base % mod;
        n >>= 1;
    }
    return res;
}
inline ll inv(ll x) {
    return qpow(x, mod - 2);
}

inline ll F(ll a1) {
    if (a1 == 1)
        return (k + mod - 1) % mod;
    ll q = a1;
    ll res = a1 * (1 + mod - qpow(q, k2)) % mod * inv((1 + mod - q) % mod) % mod;
    return (res - a1 + mod) % mod;
}

inline ll sum_2(ll x) {
    return x * (x + 1) % mod * (x * 2 + 1) % mod * inv6 % mod;
}

bool vis[M];
ll D[M];
ll getd(ll x) {
    if (x < N)
        return d[x];
    int t = n / x;
    if (vis[t])
        return D[t];
    vis[t] = 1;
    D[t] = sum_2(x);
    for (int i, j = 1; j < x;) {
        i = j + 1;
        j = x / (x / i);
        D[t] -= 1ll * (j - i + 1) * getd(x / i) % mod;
        D[t] = (D[t] + mod) % mod;
    }
    return D[t];
}

ll S(ll n) {
    ll res = 0;
    for (int i = 1, j; i <= n; i = j + 1) {
        j = n / (n / i);
        res += F(n / i) * ((getd(j) - getd(i - 1) + mod) % mod) % mod;
        res %= mod;
    }
    return res;
}

int main() {
    sieve();
    inv6 = inv(6);
    int _T;
    cin >> _T;
    while (_T--) {
        scanf("%lld%s", &n, s);
        memset(vis, 0, sizeof vis);
        k = 0;
        k2 = 0;
        for (int i = 0; s[i]; ++i) {
            k = (k * 10 + s[i] - '0') % mod;
            k2 = (k2 * 10 + s[i] - '0') % (mod - 1);
        }
        printf("%lld\n", S(n));
    }
    return 0;
}
