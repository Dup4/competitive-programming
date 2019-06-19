#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 110
const ll p = 1e9 + 7;  
int n, T;
int t[N], g[N];
ll fac[N], inv[N];
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
ll C(int n, int m) {
	if (n < m) {
		return 0;
	}
	return fac[n] * inv[n - m] % p * inv[m] % p;
}
ll f(int x, int y, int z) {
	if (x == 0 && y == 0) {
		if (z == 1) {
			return 1;
		}
	} else if (x == 0) {  
		if (y == z - 1) {
			return fac[z] * fac[y] % p;
		} 
	} else {
		if (x + y < z - 1) {
			return 0;
		} else {
			return fac[z] * C(z - 1, y) % p * C(x, z - 1 - y)
		}
	}
	return 0;
}	
	
int main() {
	fac[0] = 1;
	for (int i = 1; i <= 20; ++i) {
		fac[i] = fac[i - 1] * i % p;
	}
	inv[20] = qmod(fac[20], p - 2);
	for (int i = 20; i >= 1; --i) {
		inv[i - 1] = inv[i] * i % p;
	}
	while (scanf("%d%d", &n, &T) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d%d", t + i, g + i);
		}
		ll res = 0;
		for (int i = 0; i < (1 << n); ++i) {
			int tot = 0;
			int x[4] = {0, 0, 0};
			for (int j = 1; j <= n; ++j) {
				if ((i >> (j - 1)) & 1) {
					tot += t[j];
					++x[g[j]]; 
				}
			}
			if (tot == T) {
				sort(x + 1, x + 4);
				(res += f(x[1], x[2], x[3])) %= p; 
			}
		}
		printf("%lld\n", res); 
	}
	return 0;
}
