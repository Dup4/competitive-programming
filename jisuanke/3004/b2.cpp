#include <bits/stdc++.h>
using namespace std;

using ll = long long;
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

ll Mod(ll a, ll b) {
    return a < b ? a : a % b + b;
}

ll qpow(ll base, ll n, ll mod) {
    ll res = 1;
    while (n) {
        if (n & 1)
            res = Mod(res * base, mod);
        base = Mod(base * base, mod);
        n >>= 1;
    }
    return res;
}

ll f(int p, int cur) {
    if (cur == 0 || p == 1)
        return 1;
    int Phi = phi[p];
    return qpow(a, f(Phi, cur - 1), p);
}

int main() {
    sieve();
    int _T;
    scanf("%d", &_T);
    while (_T--) {
        scanf("%d%d%d", &a, &b, &m);
        printf("%lld\n", f(m, b) % m);
    }
    return 0;
}
