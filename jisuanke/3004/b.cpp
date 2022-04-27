#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pLI = pair<ll, int>;
#define fi first
#define se second
const int N = 1e6 + 10;
int a, b, m, pri[N], check[N], phi[N];
void sieve() {
    memset(check, 0, sizeof check);
    *pri = 0;
    phi[1] = 1;
    for (int i = 2; i < N; ++i) {
        if (!check[i]) {
            pri[++*pri] = i;
            phi[i] = i - 1;
        }
        for (int j = 1; j <= *pri; ++j) {
            if (1ll * i * pri[j] >= N)
                break;
            check[i * pri[j]] = 1;
            if (i % pri[j] == 0) {
                phi[i * pri[j]] = phi[i] * pri[j];
                break;
            } else {
                phi[i * pri[j]] = phi[i] * (pri[j] - 1);
            }
        }
    }
}

ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}

pLI qmod(ll base, ll n, ll p) {
    if (n <= 25) {
        bool F = 0;
        ll res = 1;
        for (int i = 1; i <= n; ++i) {
            res = res * base;
            if (res >= p) {
                //		puts("bug");
                F = 1;
                res %= p;
            }
        }
        return pLI(res, F);
    }
    ll res = 1;
    while (n) {
        if (n & 1)
            res = res * base % p;
        base = base * base % p;
        n >>= 1;
    }
    return pLI(res, 1);
}

pLI f(int p, int cur) {
    if (p == 1)
        return pLI(0, 1);
    if (cur == 0)
        return pLI(1, 0);
    int Phi = phi[p];
    pLI nx = f(Phi, cur - 1);
    if (gcd(a, p) == 1)
        return qmod(a, nx.fi, p);
    return qmod(a, nx.fi + nx.se * Phi, p);
}

int main() {
    sieve();
    int _T;
    scanf("%d", &_T);
    while (_T--) {
        scanf("%d%d%d", &a, &b, &m);
        if (m == 1)
            puts("0");
        else if (b == 0)
            printf("%d\n", 1 % m);
        else {
            pLI res = f(m, b);
            printf("%lld\n", res.fi);
        }
    }
    return 0;
}
