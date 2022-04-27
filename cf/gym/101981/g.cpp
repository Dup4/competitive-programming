#include <bits/stdc++.h>
using namespace std;

#define ll long long
const ll p = 1e9 + 7;
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

int main() {
    ll inv = qmod(24, p - 2);
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        printf("%lld\n", 1ll * n * (n + 1) % p * (n + 2) % p * (n + 3) % p * inv % p);
    }
    return 0;
}
