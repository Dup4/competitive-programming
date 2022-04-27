#include <bits/stdc++.h>
using namespace std;

#define ll long long
ll n, p;
const int N = 2e6 + 10;
int pri[N], check[N], tot;
void init() {
    memset(check, 0, sizeof check);
    tot = 0;
    for (int i = 2; i < N; ++i) {
        if (!check[i]) {
            pri[++tot] = i;
        }
        for (int j = 1; j <= tot; ++j) {
            if (1ll * i * pri[j] >= N)
                break;
            check[i * pri[j]] = 1;
            if (i % pri[j] == 0)
                break;
        }
    }
}

ll qpow(ll base, ll n) {
    ll res = 1;
    while (n) {
        if (n & 1)
            res = res * base % p;
        base = base * base % p;
        n >>= 1;
    }
    return res;
}

ll fact[N];
void calc(int n, int sign) {
    for (int i = 1; i <= tot; ++i) {
        ll t = pri[i];
        while (t <= n) {
            fact[i] += sign * n / t;
            t *= pri[i];
        }
    }
}

ll C(int n, int m) {
    memset(fact, 0, sizeof fact);
    calc(n, 1);
    calc(m, -1);
    calc(n - m, -1);
    ll res = 1;
    for (int i = 1; i <= tot; ++i) {
        res = res * qpow(pri[i], fact[i]) % p;
    }
    return res;
}

int main() {
    init();
    while (scanf("%lld%lld", &n, &p) != EOF) {
        printf("%lld\n", (C(2 * n, n) - C(2 * n, n - 1) + p) % p);
    }
    return 0;
}
