#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 1100
const ll p = 9999991;
int n, m;
ll f[N], fac[N], inv[N];
ll Inv[10000010];

ll qmod(ll base, ll n) {
    ll res = 1;
    while (n) {
        if (n & 1) {
            res = res * base % p;
        }
        base = base * base % p;
        n >>= 1;
    }
    return res;
}

ll solve(ll *f, int n, int x) {
    if (x <= n)
        return f[x];
    int t = (n & 1) ? -1 : 1;
    ll res = 0;
    ll base = 1;
    for (int i = 0; i <= n; ++i) base = base * (x - i) % p;
    for (int i = 0; i <= n; ++i, t *= -1) {
        res += 1ll * t * f[i] * base % p * inv[n - i] % p * inv[i] % p * Inv[x - i] % p;
        res = (res + p) % p;
    }
    return res;
}

int main() {
    fac[0] = 1;
    for (int i = 1; i < N; ++i) fac[i] = fac[i - 1] * i % p;
    inv[N - 1] = qmod(fac[N - 1], p - 2);
    for (int i = N - 1; i >= 1; --i) inv[i - 1] = inv[i] * i % p;
    Inv[1] = 1;
    for (int i = 2; i < p; ++i) Inv[i] = Inv[p % i] * (p - p / i) % p;
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 0; i <= n; ++i) scanf("%lld", f + i);
        f[n + 1] = solve(f, n, n + 1);
        for (int i = 1; i <= n + 1; ++i) f[i] = (f[i] + f[i - 1]) % p;
        int l, r;
        while (m--) {
            scanf("%d%d", &l, &r);
            printf("%lld\n", (solve(f, n + 1, r) - solve(f, n + 1, l - 1) + p) % p);
        }
    }
    return 0;
}
