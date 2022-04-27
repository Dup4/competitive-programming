#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 1000010
ll p;
int n, m;
int prime[N], mu[N];
int phi[N], inv[N], g[N];
bool check[N];

void init() {
    memset(check, 0, sizeof check);
    prime[0] = 0;
    phi[1] = 1;
    mu[1] = 1;
    for (int i = 2; i < N; ++i) {
        if (!check[i]) {
            prime[++prime[0]] = i;
            phi[i] = i - 1;
            mu[i] = -1;
        }
        for (int j = 1; j <= prime[0]; ++j) {
            if (1ll * i * prime[j] >= N)
                break;
            check[i * prime[j]] = 1;
            if (i % prime[j] == 0) {
                phi[i * prime[j]] = phi[i] * prime[j];
                mu[i * prime[j]] = 0;
                break;
            } else {
                phi[i * prime[j]] = phi[i] * (prime[j] - 1);
                mu[i * prime[j]] = -mu[i];
            }
        }
    }
}

void work() {
    inv[1] = 1;
    for (int i = 2; i <= n; ++i) inv[i] = 1ll * inv[p % i] * (p - p / i) % p;
    for (int i = 1; i <= n; ++i) g[i] = 1ll * i * inv[phi[i]] % p;
}

ll get(int n, int m) {
    ll res = 0;
    for (int i = 1; i <= n; ++i) res = (res + 1ll * mu[i] * (n / i) * (m / i)) % p;
    return res;
}

int main() {
    init();
    int T;
    cin >> T;
    while (T--) {
        scanf("%d %d %lld\n", &n, &m, &p);
        if (n > m)
            swap(n, m);
        work();
        ll res = 0;
        for (int i = 1; i <= n; ++i) res = (res + g[i] * get(n / i, m / i)) % p;
        printf("%lld\n", res);
    }
    return 0;
}
