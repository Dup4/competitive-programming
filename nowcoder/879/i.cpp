#include <bits/stdc++.h>
using namespace std;

#define N 10000010
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
int n, k;
int prime[N];
bool check[N];
ll f[N], g[N], h[N], y[N], d[N];
void init() {
    memset(check, 0, sizeof check);
    prime[0] = 0;
    f[1] = 1;
    g[1] = 1;
    for (int i = 2; i < N; ++i) {
        if (!check[i]) {
            prime[++prime[0]] = i;
            d[i] = qmod(i, k);
            g[i] = d[i];
            h[i] = g[i];
            y[i] = i;
            f[i] = g[i] + 1;
        }
        for (int j = 1; j <= prime[0]; ++j) {
            if (1ll * i * prime[j] >= N) {
                break;
            }
            check[i * prime[j]] = 1;
            if (i % prime[j] == 0) {
                y[i * prime[j]] = y[i] * prime[j] % p;
                h[i * prime[j]] = h[i] * d[prime[j]] % p;
                g[i * prime[j]] = (g[i] + h[i * prime[j]]) % p;
                f[i * prime[j]] = (f[i] / y[i]) * f[y[i * prime[j]]] % p;
                break;
            } else {
                f[i * prime[j]] = f[i] * f[prime[j]] % p;
                g[i * prime[j]] = g[prime[j]];
                h[i * prime[j]] = h[prime[j]];
                y[i * prime[j]] = prime[j];
            }
        }
    }
}

int main() {
    while (scanf("%d%d", &n, &k) != EOF) {
        init();
        ll res = 0;
        for (int i = 1; i <= n; ++i) {
            res = (res + f[i]) % p;
        }
        printf("%lld\n", res);
    }
    return 0;
}
