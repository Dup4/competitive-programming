#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 200010
const ll p = 1e9 + 7;
int n, m, k;
ll fac[N], inv[N];
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
ll C(int n, int m) {
    return fac[n] * inv[m] % p * inv[n - m] % p;
}
ll f(int n) {
    return (1ll * n * (n + 1) / 2) % p;
}

int main() {
    fac[0] = 1;
    for (int i = 1; i < N; ++i) {
        fac[i] = (fac[i - 1] * i % p);
    }
    inv[200000] = qmod(fac[200000], p - 2);
    for (int i = 200000; i >= 1; --i) {
        inv[i - 1] = (inv[i] * i % p);
    }
    while (scanf("%d%d%d", &n, &m, &k) != EOF) {
        ll res = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                ll tot = ((f(j - 1) + f(m - j)) * n % p + (f(i - 1) + f(n - i)) * m % p) % p;
                (res += tot * C(n * m - 2, k - 2) % p) %= p;
            }
        }
        printf("%lld\n", res * qmod(2, p - 2) % p);
    }
    return 0;
}
