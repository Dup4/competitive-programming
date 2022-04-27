#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
const ll p = (ll)1e9 + 7;
int n;
int prime[N], mu[N];
bool check[N];
vector<int> fac[N];
void init() {
    memset(check, 0, sizeof check);
    prime[0] = 0;
    mu[1] = 1;
    for (int i = 2; i < N; ++i) {
        if (!check[i]) {
            prime[++prime[0]] = i;
            mu[i] = -1;
        }
        for (int j = 1; j <= prime[0]; ++j) {
            if (1ll * i * prime[j] >= N) {
                break;
            }
            check[i * prime[j]] = 1;
            if (i % prime[j] == 0) {
                mu[i * prime[j]] = 0;
                break;
            } else {
                mu[i * prime[j]] = -mu[i];
            }
        }
    }
    for (int i = 1; i < N; ++i) {
        for (int j = i; j < N; j += i) {
            fac[j].push_back(i);
        }
    }
}
ll f[N], inv[N];

int main() {
    init();
    while (scanf("%d", &n) != EOF) {
        inv[1] = 1;
        for (int i = 2; i <= n; ++i) {
            inv[i] = inv[p % i] * (p - p / i) % p;
        }
        f[1] = 1;
        for (int i = 2; i <= n; ++i) {
            ll t = 0;
            for (auto it : fac[i])
                if (it != i) {
                    ll tt = 0;
                    for (auto it2 : fac[i / it]) {
                        tt = (tt + mu[it2] * (n / it / it2) % p + p) % p;
                    }
                    t = (t + f[it] * tt % p) % p;
                }
            f[i] = (1 + t * inv[n] % p) % p;
            f[i] = f[i] * n % p * inv[n - n / i] % p;
        }
        ll res = 0;
        for (int i = 1; i <= n; ++i) {
            res = (res + f[i]) % p;
        }
        printf("%lld\n", res * inv[n] % p);
    }
    return 0;
}
