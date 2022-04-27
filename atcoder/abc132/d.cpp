#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 2010
const int p = 1e9 + 7;
int n, k;
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
    if (n < m)
        return 0;
    return fac[n] * inv[m] % p * inv[n - m] % p;
}

ll f(int n, int i, int k) {
    ll remind = n - k;
    if (n - k < i - 1) {
        return 0;
    }
    remind -= i - 1;
    return C(k - 1, i - 1) * C(i + remind, i) % p;
}

int main() {
    fac[0] = 1;
    for (int i = 1; i <= 2000; ++i) {
        fac[i] = fac[i - 1] * i % p;
    }
    inv[2000] = qmod(fac[2000], p - 2);
    for (int i = 2000; i >= 0; --i) {
        inv[i - 1] = inv[i] * i % p;
    }
    while (scanf("%d%d", &n, &k) != EOF) {
        for (int i = 1; i <= k; ++i) {
            printf("%lld\n", f(n, i, k));
        }
    }
    return 0;
}
