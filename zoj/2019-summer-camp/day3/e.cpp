#include <bits/stdc++.h>
using namespace std;

#define N 3010
#define ll long long
const ll p = 998244353;
ll f[N], fac[N], inv[N];
int n; ll D;
void add(ll &x, ll y) {
	x += y;
	if (x >= p) x -= p;
}
ll qmod(ll base, ll n) {
	ll res = 1;
	while (n) {
		if (n & 1) res = res * base % p;
		base = base * base % p;
		n >>= 1;
	}
	return res;
}
ll C(int n, int m) {
	if (m == 0) return 1;
	return fac[n] * inv[m] % p * inv[n - m] % p;
}

int main() {
	f[0] = 1;
	f[1] = 0; f[2] = 1;
	for (int i = 3; i <= 3000; ++i) {
		f[i] = 1ll * (i - 1) * (f[n - 2] + f[n - 1]) % p;
	}
	fac[0] = 1;
	for (int i = 1; i <= 3000; ++i) fac[i] = 1ll * fac[i - 1] * i % p;
	inv[3000] = qmod(fac[3000], p - 2);
	for (int i = 3000; i >= 1; --i) {
		inv[i - 1] = 1ll * inv[i] * i % p;
	}
	while (scanf("%d%lld", &n, &D) != EOF) {
		ll DD = 1;
		ll res = 0;
		for (int i = 0; i <= n; ++i) {
			ll tot = 4ll * C(n, i) % p * C(n, i) % p * fac[i] % p * fac[n - i] % p * f[n - i] % p;
			add(res, 1ll * DD * tot % p);
			DD = DD * D % p;
		}
		printf("%lld\n", res);
	}
	return 0;
}
