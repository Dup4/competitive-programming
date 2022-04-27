#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int N = 1e5 + 10;
const ll mod = 1e9 + 7;
int n, k, l, r;
ll f[N];

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

int main() {
    scanf("%d%d%d%d", &n, &k, &l, &r);
    memset(f, 0, sizeof f);
    if (l <= k && k <= r)
        f[1] = 1;
    l = (l - 1) / k, r /= k;
    for (int i = r - l; i >= 1; --i) {
        ll L = l / i, R = r / i;
        f[i] = (f[i] + qpow(R - L, n) - (R - L) + mod) % mod;
        for (int j = i << 1; j < N; j += i) f[i] = (f[i] + mod - f[j]) % mod;
    }
    printf("%lld\n", f[1]);
    return 0;
}
