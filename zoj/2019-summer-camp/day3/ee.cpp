#include <bits/stdc++.h>
using namespace std;

#define N 6010
#define ll long long
const ll p = 998244353;
int n; ll D;
ll f[N], g[N], fac[N], inv[N];
ll qmod(ll base, ll n) {
	ll res = 1;
	while (n) {
		if (n & 1) res = res * base % p;
		base = base * base % p;
		n >>= 1;
	}
	return res;
}
ll c(int n, int m) {
	return fac[n] * inv[n - m] % p * inv[m] % p;
}

int main() {
	fac[0] = 1;
	for (int i = 1; i <= 6000; ++i) fac[i] = fac[i - 1] * i % p;
	inv[6000] = qmod(fac[6000], p - 2);
	for (int i = 6000; i >= 1; --i) inv[i - 1] = inv[i] * i % p;
	while (scanf("%d%lld", &n, &D) != EOF) {
		
	}
	return 0;
}
