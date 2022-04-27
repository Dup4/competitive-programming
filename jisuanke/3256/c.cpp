#include <bits/stdc++.h>
using namespace std;

#define ll long long
const ll p = 998244353;

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

int main() {
    int n;
    while (scanf("%d", &n) != EOF) {
        if (n == 1)
            printf("1\n");
        else if (n == 2)
            puts("2");
        else {
            printf("%lld\n", 1ll * n * (n - 1) % p * qmod(n - 1, n - 3) % p);
        }
    }
    return 0;
}
