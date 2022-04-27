#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 6010
#define M 6000
const ll p = 998244353;
void add(ll &x, ll y) {
    x += y;
    if (x >= p)
        x -= p;
}
int n;
ll g[N], fac[N], inv[N], D;
ll qmod(ll base, ll n) {
    ll res = 1;
    while (n) {
        if (n & 1)
            res = res * base % p;
        base = base * base % p;
        n >>= 1;
    }
    return res;
}
ll C(int n, int m) {
    if (n < m)
        return 0;
    if (m == 0)
        return 1;
    return fac[n] * inv[n - m] % p * inv[m] % p;
}

ll F(int x) {
    g[0] = fac[2 * x];
    for (int i = 1; i <= x; ++i) g[i] = C(x, i) * C(x, i) % p * fac[i] % p * qmod(2, i) % p * fac[2 * (x - i)] % p;
    ll res = 0, A;
    for (int i = 0; i <= x; ++i) {
        if (i & 1)
            A = (p - g[i]) % p;
        else
            A = g[i];
        add(res, A);
    }
    return res;
}

int main() {
    fac[0] = 1;
    for (int i = 1; i <= M; ++i) fac[i] = fac[i - 1] * i % p;
    inv[M] = qmod(fac[M], p - 2);
    for (int i = M; i >= 1; --i) inv[i - 1] = inv[i] * i % p;
    while (scanf("%d%lld", &n, &D) != EOF) {
        ll DD = 1;
        ll res = 0;
        for (int i = 0; i <= n; ++i) {
            add(res, DD * C(n, i) % p * C(n, i) % p * fac[i] % p * qmod(2, i) % p * F(n - i) % p);
            DD = DD * D % p;
        }
        printf("%lld\n", res);
    }
    return 0;
}
