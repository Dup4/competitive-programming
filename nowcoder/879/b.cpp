#include <bits/stdc++.h>
using namespace std;

#define N 100010
#define ll long long
const ll mod = 998244353;
int n, k, p;
ll fac[N], inv[N];
ll qmod(ll base, ll n) {
    ll res = 1;
    while (n) {
        if (n & 1) {
            res = res * base % mod;
        }
        base = base * base % mod;
        n >>= 1;
    }
    return res;
}
ll C(int n, int m) {
    return fac[n] * inv[m] % mod * inv[n - m] % mod;
}

int main() {
    fac[0] = 1;
    for (int i = 1; i < N; ++i) {
        fac[i] = (fac[i - 1] * i) % mod;
    }
    inv[100000] = qmod(fac[100000], mod - 2);
    for (int i = 100000; i >= 1; --i) {
        inv[i - 1] = (inv[i] * i) % mod;
    }
    while (scanf("%d%d%d", &n, &k, &p) != EOF) {
        int fp = (1 - p + mod) % mod;
        ll res = 0;
        ll base = qmod(p, k);
        for (int i = k; i <= n; ++i) {
            (res += C(n, i) * base % mod * qmod(fp, n - i)) %= mod;
            base = base * p % mod;
        }
        printf("%lld\n", res);
    }
    return 0;
}
