#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int M = 1e3 + 10;
const int N = 1e6 + 10;
int n, p, f[N], fac[M], inv[M];
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
	return 1ll * fac[n] * inv[m] % p * inv[n - m] % p;
}
int DFS(int n) {
	if (f[n] != -1) return f[n];
	return f[n] = (DFS(n - p) + DFS(n - p + 1)) % p;
}

int main() { 
	int _T; scanf("%d", &_T);
	while (_T--) {
		scanf("%d%d", &n, &p);
		fac[0] = 1;
		for (int i = 1; i < p; ++i) fac[i] = fac[i - 1] * i % p;
	   	inv[p - 1] = qpow(fac[p - 1], p - 2);
		for (int i = p - 1; i >= 1; --i) inv[i - 1] = inv[i] * i % p;
		memset(f, -1, sizeof f);
		f[0] = 1; 
		for (int i = 1; i <= p; ++i) { 
			f[i] = 0;
			for (int j = 0; j < i; ++j) {
				f[i] = (f[i] + 1ll * C(i - 1, j) * f[j] % p) % p;
			}
		}
		printf("%d\n", DFS(n));
	}
	return 0;
}
