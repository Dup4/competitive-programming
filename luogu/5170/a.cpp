#include <bits/stdc++.h>
using namespace std;

#define ll long long
const ll p = 998244353;
const ll mod = 998244353;
ll n, a, b, c, inv2;

ll qmod(ll base, ll n) {
    ll res = 1;
    while (n) {
        if (n & 1)
            res = res * base % p;
        ;
        base = base * base % p;
        n >>= 1;
    }
    return res;
}

ll f1(ll a, ll b, ll c, ll n) {
    if (!a)
        return (b / c * (n + 1)) % p;
    if (n == 0)
        return b / c;
    if (a >= c || b >= c) {
        return (f1(a % c, b % c, c, n) + ((a / c) % p * ((n * (n + 1) / 2) % p)) % p + (b / c) * (n + 1) % p) % p;
    }
    ll m = (a * n + b) / c;
    return (n * m % p - f1(c, c - b - 1, a, m - 1)) % p;
}

int main() {
    inv2 = qmod(2, p - 2);
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%lld%lld%lld%lld", &n, &a, &b, &c);
        printf("%lld 0 0\n", (f1(a, b, c, n) + p) % p);
    }
    return 0;
}
