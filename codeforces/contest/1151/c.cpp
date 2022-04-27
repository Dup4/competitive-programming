#include <bits/stdc++.h>
using namespace std;

#define ll long long
const ll p = (ll)1e9 + 7;
ll inv;
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
ll ql, qr;
ll g(ll st, ll len) {
    len %= p;
    ll ed = (st + 2ll * ((len - 1 + p) % p) % p) % p;
    return (st + ed) % p * len % p * inv % p;
}
ll f(ll x) {
    ll res = 0, len = 0, st[2] = {1, 2};
    for (ll i = 1, j = 0;; i <<= 1, j ^= 1) {
        if (i + len >= x) {
            res = (res + g(st[j], x - len));
            break;
        } else {
            res = (res + g(st[j], i)) % p;
            st[j] = (st[j] + 1ll * 2 * (i % p) % p) % p;
            len += i;
        }
    }
    return res;
}

int main() {
    inv = qmod(2, p - 2);
    while (scanf("%lld%lld", &ql, &qr) != EOF) {
        printf("%lld\n", (f(qr) - f(ql - 1) + p) % p);
    }
    return 0;
}
