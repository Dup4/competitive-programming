#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 3e3 + 10;
const int mod = 998244353;
int n, m, A, B, fac[N], inv[N];
ll f[N];
ll qpow(ll base, ll n) {
	ll res = 1;
	while (n) {
		if (n & 1) res = res * base % mod;
		base = base * base % mod;
		n >>= 1;
	}
	return res;
}
ll C(int n, int m) {
	if (n < m) return 0;
	return 1ll * fac[n] * inv[m] % mod * inv[n - m] % mod;
}

int main() {
	fac[0] = 1;
	for (int i = 1; i < N; ++i) fac[i] = 1ll * fac[i - 1] * i % mod;
	inv[N - 1] = qpow(fac[N - 1], mod - 2);
	for (int i = N - 1; i >= 1; --i) inv[i - 1] = 1ll * inv[i] * i % mod;
	while (scanf("%d%d%d%d", &n, &m, &A, &B) != EOF) {
		memset(f, 0, sizeof f);
		//f[i]表示 至少有A行全黑，并且恰好有i列全黑的方案数
		for (int i = 0; i <= m; ++i) { 
			ll p = (qpow(2, n - A) - 1 + mod) % mod;
			f[i] = C(n, A) * C(m, i) % mod * qpow(p, m - i) % mod;
		}
		ll ans = 0; 
		for (int i = B; i <= m; ++i) ans = (ans + f[i]) % mod;
		printf("%lld\n", ans);
	}
	return 0;
}
