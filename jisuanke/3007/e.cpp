#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e6 + 10;
int n, p; ll f[N], g[N], fac[N], inv[N];
ll qpow(ll base, ll n) {
	ll res = 1;
	while (n) {
		if (n & 1) res = res * base % p;
		base = base * base % p;
		n >>= 1;
	}
	return res;
}
ll C(int n, int m) {
	if (n < m) return 0;
	ll a = 1, b = 1;
	for (int i = n; i >= n - m + 1; --i) a = a * i;
	for (int i = 1; i <= m; ++i) b = b * i;
	return (a / b) % p;
}

int main() {
	int _T; scanf("%d", &_T);
	while (_T--) {
		scanf("%d%d", &n, &p);
		fac[0] = 1;
		for (int i = 1; i < N; ++i) fac[i] = fac[i - 1] * i % p;
		inv[N - 1] = qpow(fac[N - 1], p - 2);
		for (int i = N - 1; i >= 1; --i) inv[i - 1] = inv[i] * i % p; 
		for (int i = 0; i <= n; ++i) f[i] = qpow(i, n); 
	//	for (int i = 0; i <= n; ++i) cout << f[i] << endl;
		ll res = 0;
		for (int i = 1; i <= n; ++i) {
			g[i] = 0;
			for (int j = 0, t = ((i & 1) ? -1 : 1); j <= i; ++j, t *= -1) {
				g[i] += 1ll * t * C(i, j) * f[j] % p;
				g[i] = (g[i] % p + p) % p;
			}
			cout << i << " " << f[i] << endl;
			res = (res + g[i]) % p;
		}
		cout << res << endl;
	}
	return 0;
}
