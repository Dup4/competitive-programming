#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 10000100
#define M 10000100
ll p, n, inv, inv6;
ll phi[N];
int prime[N];
bool check[N];
void init() {
    memset(check, 0, sizeof check);
    prime[0] = 0;
    phi[1] = 1;
    for (int i = 2; i < N; ++i) {
        if (!check[i]) {
            prime[++prime[0]] = i;
            phi[i] = i - 1;
        }
        for (int j = 1; j <= prime[0]; ++j) {
            if (1ll * i * prime[j] >= N)
                break;
            check[i * prime[j]] = 1;
            if (i % prime[j] == 0) {
                phi[i * prime[j]] = phi[i] * prime[j] % p;
                break;
            } else
                phi[i * prime[j]] = phi[i] * (prime[j] - 1) % p;
        }
    }
    for (int i = 2; i < N; ++i) phi[i] = (phi[i - 1] + 1ll * i * i % p * phi[i] % p) % p;
}
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

ll f2(ll x) {
    x %= p;
    return x * (x + 1) % p * (x * 2 % p + 1) % p * inv6 % p;
}
ll f3(ll x) {
    x %= p;
    return x * x % p * (x + 1) % p * (x + 1) % p * inv % p * inv % p;
}

ll SS[M];
bool vis[M];
ll S(ll x) {
    if (x < N)
        return phi[x];
    int t = n / x;
    if (vis[t])
        return SS[t];
    vis[t] = 1;
    ll tot = f3(x);
    for (ll i = 2, j; i <= x; i = j + 1) {
        j = x / (x / i);
        tot = (tot - (f2(j) - f2(i - 1) + p) % p * S(x / i) % p + p) % p;
    }
    return SS[t] = tot;
}

int main() {
    scanf("%lld %lld\n", &p, &n);
    init();
    inv = qmod(2, p - 2);
    inv6 = qmod(6, p - 2);
    memset(vis, 0, sizeof vis);
    ll res = 0;
    for (ll i = 1, j; i <= n; i = j + 1) {
        j = n / (n / i);
        res = (res + f3(n / i) % p * (S(j) - S(i - 1) + p) % p) % p;
    }
    printf("%lld\n", res);
    return 0;
}
