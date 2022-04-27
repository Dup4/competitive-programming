#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll mod = 10092272478850909;

ll mul(ll u, ll v) {
    return (u * v - (ll)((long double)u * v / mod) * mod + mod) % mod;
}

ll qpow(ll base, ll n) {
    ll res = 1;
    while (n) {
        if (n & 1)
            res = mul(res, base);
        base = mul(base, base);
        n >>= 1;
    }
    return res;
}

ll sum(ll p, ll n) {
    if (p == 0)
        return 0;
    if (n == 0)
        return 1;
    if (n & 1) {
        return (mul(1 + qpow(p, n / 2 + 1), sum(p, n / 2))) % mod;
    } else {
        return (mul(1 + qpow(p, n / 2 + 1), sum(p, n / 2 - 1)) + qpow(p, n / 2)) % mod;
    }
}

int main() {
    int n;
    while (scanf("%d", &n) != EOF) {
        ll res = 0;
        for (int i = 1; i <= n; ++i) {
            res += sum(i, n);
            res %= mod;
        }
        res = (res - n + mod) % mod;
        printf("%lld\n", res);
    }
    return 0;
}
