#include <bits/stdc++.h>
using namespace std;

#define N 100010
#define ll long long
const ll p = 998244353;
ll qmod (ll base, ll n) {
	ll res = 1;
	while (n) {
		if (n & 1) {
			res = res * base % p;
		}
		base = base * base % p;
		n >>= 1;
	}
	return res;
}
ll fac[N], inv[N];
ll C(int n, int m) {
	return fac[n] * inv[m] % p * inv[n - m] % p;
}

int n, x, y;
int main() {
	fac[0] = 1;
	for (int i = 1; i <= 100000; ++i) {
		fac[i] = (fac[i - 1] * i) % p;
	}
	inv[100000] = qmod(fac[100000], p - 2);
	for (int i = 100000; i >= 1; --i) {
		inv[i - 1] = (inv[i] * i) % p;
	}
	while (scanf("%d%d%d", &n, &x, &y) != EOF) {
		ll res = 0;
		ll base = 1ll * x * qmod(y, p - 2) % p;
		for (int i = 0; i <= n; ++i) {
			(res += C(n, i) * qmod(base, (1ll * i * (i - 1) / 2)) % p) %= p;
		}
		printf("%lld\n", res);
	}
	return 0;
}
