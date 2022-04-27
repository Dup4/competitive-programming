#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 1000100
const ll p = (ll)1e9 + 9, inv2 = 500000005;
int prime[N], mu[N];
bool check[N];
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
        mu[i] *= i;
    }
}
ll n;
ll g(ll n) {
    n %= p;
    ll a = n, b = n + 1;
    if (a % 2 == 0) {
        a /= 2;
    } else {
        b /= 2;
    }
    return a * b % p;
}
map<ll, ll> mp;
ll s(ll n) {
    if (mp.find(n) != mp.end()) {
        return mp[n];
    }
    ll res = 0;
    for (ll i = 1, j; i <= n; i = j + 1) {
        j = n / (n / i);
        res = (res + (g(j) - g(i - 1) + p) % p * (n / i) % p) % p;
    }
    return mp[n] = res;
}

int main() {
    init();
    mp.clear();
    while (scanf("%lld", &n) != EOF) {
        ll limit = sqrt(n) + 1;
        ll res = 0;
        for (int i = 1; i <= limit; ++i) {
            res = (res + (1ll * mu[i] * s(n / i / i)) % p + p) % p;
        }
        printf("%lld\n", (res + p) % p);
    }
    return 0;
}
