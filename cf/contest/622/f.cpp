#include <bits/stdc++.h>
using namespace std;

#define N 1000010
#define ll long long
const ll p = 1e9 + 7;
int n, k;
ll f[N];
template <typename T>
void add(T &x, T y) {
	x += y;
	if (x >= p) {
		x -= p;
	}
}
ll qmod(ll base, ll n) {
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

int main() {
	fac[0] = 1;
	for (int i = 1; i < N; ++i) {
		fac[i] = fac[i - 1] * i % p;
	}
	inv[N - 1] = qmod(fac[N - 1], p - 2);
	for (int i = N - 1; i >= 1; --i) {
		inv[i - 1] = inv[i] * i % p; 
	}
	while (scanf("%d%d", &n, &k) != EOF) {
		f[0] = 0;
		for (int i = 1; i <= k + 1; ++i) {
			f[i] = qmod(i, k);
			add(f[i], f[i - 1]);
		}
		if (n <= k + 1) {
			printf("%lld\n", f[n]);
		} else {
			int t = (k & 1) ? 1 : -1;
			ll res = 0; 
			ll base = n;
			for (int i = 1; i <= k + 1; ++i) {
				base = base * (n - i) % p;
			}
			for (int i = 0; i <= k + 1; ++i, t *= -1) {
				ll tmp = 1ll * t * f[i] * base % p * inv[k + 1 - i] % p * inv[i] % p * qmod(n - i, p - 2) % p;
				add(res, (tmp + p) % p);
			}
			printf("%lld\n", res);
		}
		
	}
	return 0;
}
