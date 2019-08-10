#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int N = 2e3 + 10;
const ll p = 1e9 + 7;
int n, m;
ll fac[N], inv[N];

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
	if (m > n) return 0;
	return fac[n] * inv[m] % p * inv[n - m] % p;
}

int main() {
	fac[0] = 1;
	for (int i = 1; i < N; ++i) fac[i] = fac[i - 1] * i % p;
	inv[N - 1] = qmod(fac[N - 1], p - 2);
	for (int i = N - 1; i >= 1; --i) inv[i - 1] = inv[i] * i % p;
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		ll res = C(n + m - 2, m - 1);
	//	for (int i = 1; i <= m; ++i) {
	//		if (i > n) break;
	//		res += C(m - 1, i - 1) * C(n - 1, i - 1) % p;
	//		res %= p;
	//	}
		printf("%lld\n", res);
	}
	return 0;
}
