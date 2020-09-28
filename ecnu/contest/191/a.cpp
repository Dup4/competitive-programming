#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
#define pii pair <int, int>
#define fi first
#define se second
pii fac[N]; int tot;
int n;

int qpow(int base, int n) {
	int res = 1;
	while (n) {
		if (n & 1) res = res * base;
		base = base * base;
		n >>= 1;
	}
	return res;
}

void getfac(pii *fac, int t) { 
	tot = 0;
	for (int i = 2; i * i <= t; ++i) {
		if (t % i == 0) {
			fac[++tot] = pii(i, 0);
			while (t % i == 0) {
				++fac[tot].se;
				t /= i;
			}
		}
	}
	if (t != 1) fac[++tot] = pii(t, 1); 
}

bool issquare(ll x) {
	ll limit = sqrt(x);
   	int l = max(1ll, limit - 10), r = min(x, limit + 10);
	for (int i = l; i <= r; ++i) {
		if (1ll * i * i == x) return 1;
	}	
	return 0;
}

bool isprime(int x) {
	for (int i = 2; i * i <= x && i < x; ++i) {
		if (x % i == 0) {
			return 0;
		}
	}
	return 1;
}

int get(int n) {
	for (int i = n - 1; i >= 1; --i) {
		if (issquare(1ll * i * n)) {
			return i;		
		}
	}
	return 0;
}

int main() {
	while (scanf("%d", &n) != EOF) {
		if (issquare(n)) {
			printf("%d\n", n);
		} else if (isprime(n)) {
			puts("-1");
		} else {
			int res = get(n);
			getfac(fac, n);
			int cnt = 0; 
	    	int base = 1; 
			for (int i = 1; i <= tot; ++i) {
				if (fac[i].se & 1) {
					++cnt;
					base *= qpow(fac[i].fi, fac[i].se - 1);
				} else {
					base *= qpow(fac[i].fi, fac[i].se);
				}
			}
			if (cnt == tot) {
				for (int i = 1; i < 1 << tot; ++i) {
					int l = 1, r = 1;
					for (int j = 0; j < tot; ++j) {
						if ((i >> j) & 1) {
							l *= fac[j + 1].fi;
						} else {
							r *= fac[j + 1].fi;
						}
					}
					if (l != r && l != n && r != n) {
						while (l * 2 < n && r * 2 < n) l *= 2, r *= 2;
						res = max(res, base * min(l, r));
					}
				}
			}
			printf("%d\n", res);
		}
	}
	return 0;
}
