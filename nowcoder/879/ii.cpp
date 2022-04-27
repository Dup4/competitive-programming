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
ll f[N], g[N];
void init() {
    memset(check, 0, sizeof check);
    prime[0] = 0;
    for (int i = 2; i < N; ++i) {
        if (!check[i]) {
            prime[++prime[0]] = i;
        }
        for (int j = 1; j <= prime[0]; ++j) {
            if (1ll * i * prime[j] >= N) {
                break;
            }
            check[i * prime[j]] = 1;
            if (i % prime[j] == 0) {
                break;
            }
        }
    }
    g[1] = 1;
    for (int i = 1; i <= prime[0]; ++i) {
        ll base = qmod(prime[i], k);
        ll add = 1;
        ll tot = 1;
        g[prime[i]] = prime[i];
        for (int j = 1; 1ll * j * prime[i] < N;) {
            j *= prime[i];
            add = (add * base) % p;
            tot = (tot + add) % p;
            f[j] = tot;
            g[j] = g[j / prime[i]] * prime[i];
        }
    }
    f[1] = 1;
    for (int i = 2; i < N; ++i) {
        for (int j = 1; j <= prime[0]; ++j) {
            if (1ll * i * prime[j] >= N) {
                break;
            }
            if (i % prime[j] == 0) {
                if (i / g[i] != 1) {
                    g[i * prime[j]] = g[i] * prime[j];
                    f[i * prime[j]] = (f[i / g[i]]) * f[g[i * prime[j]]] % p;
                }
                break;
            } else {
                f[i * prime[j]] = f[i] * f[prime[j]] % p;
                g[i * prime[j]] = prime[j];
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
