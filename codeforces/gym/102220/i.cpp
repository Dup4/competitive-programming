#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 400010
const ll p = 998244353;
int n, a[N];
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
ll fac[N], inv[N];

int main() {
    fac[0] = 1;
    for (int i = 1; i < N; ++i) {
        fac[i] = fac[i - 1] * i % p;
    }
    inv[N - 1] = qmod(fac[N - 1], p - 2);
    for (int i = N - 1; i >= 1; --i) {
        inv[i - 1] = inv[i] * i % p;
    }
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
        }
        n = unique(a + 1, )
    }
    return 0;
}
