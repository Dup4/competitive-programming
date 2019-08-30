#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int N = 2e6 + 10;
const int M = 1e5 + 10;
const ll mod = 1e9 + 7;
int pri[N], check[N], phi[N], tot;
ll f[N], F[N], inv2, inv6, n;
void init() {
    memset(check, 0, sizeof check);
    tot = 0;
    phi[1] = 1;
    for (int i = 2; i < N; ++i) {
        if (!check[i]) {
            pri[++tot] = i;
            phi[i] = i - 1;
        } 
        for (int j = 1; j <= tot; ++j) {
            if (1ll * i * pri[j] >= N) break;
            check[i * pri[j]] = 1;
            if (i % pri[j] == 0) {
                phi[i * pri[j]] = phi[i] * pri[j];
                break;
            } else {
                phi[i * pri[j]] = phi[i] * (pri[j] - 1); 
            }
        }
    }
    f[1] = 0;
    for (int i = 1; i < N; ++i) {
        f[i] = f[i - 1];
        f[i] += 1ll * i * phi[i] % mod;
        f[i] %= mod;
    }
}

ll qpow(ll base, ll n) {
    ll res = 1;
    while (n) {
        if (n & 1) res = res * base % mod;
        base = base * base % mod;
        n >>= 1;
    }
    return res;
}

ll sum_2(ll n) {
    return n * (n + 1) % mod * (2 * n + 1) % mod * inv6 % mod;
}

ll sum(ll n) {
    return n * (n + 1) % mod * inv2 % mod;
}

bool vis[M]; 
ll S(ll x) {
    if (x < N) return f[x];
	int t = n / x;
	if (vis[t]) return F[t];
	vis[t] = 1;
    ll res = sum_2(x);
    for (int i, j = 1; j < x; ) {
        i = j + 1;
        j = x / (x / i);
        res += mod - (sum(j) - sum(i - 1) + mod) % mod * S(x / i) % mod;
        res = res % mod;
    }
	return F[t] = res;
}

int main() {
    init();
    inv2 = qpow(2, mod - 2); inv6 = qpow(6, mod - 2);
    scanf("%lld\n", &n);
	memset(vis, 0, sizeof vis);
    printf("1\n%lld\n", S(n));
    return 0;
}