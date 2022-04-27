#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 1100
const ll p = 1e9 + 7;
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
int n, k;
int a[N];
ll C(int n, int m) {
    if (n < m) {
        return 0;
    }
    return fac[n] * inv[m] % p * inv[n - m] % p;
}

int main() {
    fac[0] = 1;
    for (int i = 1; i <= 1000; ++i) {
        fac[i] = (fac[i - 1] * i) % p;
    }
    inv[1000] = qmod(fac[1000], p - 2);
    for (int i = 1000; i >= 1; --i) {
        inv[i - 1] = (inv[i] * i) % p;
    }
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &k);
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
        }
        sort(a + 1, a + 1 + n);
        ll res = 0;
        for (int i = 1; i <= n; ++i) {
            (res += C(n - i, k - 1) * a[i] % p) %= p;
        }
        printf("%lld\n", res);
    }
    return 0;
}
