#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int N = 1e6 + 110;
const ll mod = 1e6 + 3;
ll fac[N], inv[N];
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
    if (n < m)
        return 0;
    return fac[n] * inv[m] % mod * inv[n - m] % mod;
}
ll Lucas(ll n, ll m) {
    if (n < m)
        return 0;
    if (m == 0)
        return 1;
    return Lucas(n / mod, m / mod) * C(n % mod, m % mod) % mod;
}

int main() {
    fac[0] = 1;
    for (int i = 1; i < mod; ++i) fac[i] = fac[i - 1] * i % mod;
    inv[mod - 1] = qpow(fac[mod - 1], mod - 2);
    for (int i = mod - 1; i >= 1; --i) inv[i - 1] = inv[i] * i % mod;
    int T;
    cin >> T;
    while (T--) {
        ll n, m, l, r;
        scanf("%lld%lld%lld", &n, &l, &r);
        m = r - l + 1;
        printf("%lld\n", (Lucas(n + m, m) + mod - 1) % mod);
    }
    return 0;
}
