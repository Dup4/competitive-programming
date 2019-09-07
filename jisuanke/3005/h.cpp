#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll mod = 1e9 + 7;
const int S = 1e6;
mt19937 rd(time(0));
inline ll gcd(ll a, ll b) {
	return b ? gcd(b, a % b) : a;
}
inline ll mul(ll a, ll b, ll p) {
	return (a * b - (ll)(a / (long double)p * b + 1e-3) * p + p) % p;
}
inline ll qmod(ll base, ll n, ll p) {
	ll res = 1;
	base %= p;
	while (n) {
		if (n & 1) {
			res = mul(res, base, p);
		}
		base = mul(base, base, p);
		n >>= 1;
	}
	return res;
}
struct Mill {
	ll n, fac[220]; int tot; 
	const int C = 2307;
	const int S = 10;
	inline bool check(ll a, ll n) {
		ll m = n - 1, x, y;
		int j = 0;
		while (!(m & 1)) {
			m >>= 1;
			++j;
		}
		x = qmod(a, m, n);
		for (int i = 1; i <= j; x = y, ++i) {
			y = mul(x, x, n);
			if (y == 1 && x != 1 && x != n - 1) {
				return 1;
			}
		}
		return y != 1;
	}
	inline bool miller_rabin(ll n) {
		if (n < 2) {
			return 0;
		} else if (n == 2) {
			return 1;
		
		} else if (! (n & 1)) {
			return 0;
		}
		for (int i = 0; i < S; ++i) {
			if (check(rd() % (n - 1) + 1, n)) {
				return 0;
			}
		}
		return 1;
	}
	inline ll pollard_rho(ll n, int c) {
		ll i = 1, k = 2, x = rd() % n, y = x, d;
		while (1) {
			++i; x = (mul(x, x, n) + c) % n;
			d = gcd(y - x, n);
			if (d > 1 && d < n) {
				return d;
			}
			if (y == x) {
				return n;
			}
			if (i == k) {
				y = x;
				k <<= 1;
			}
		}
	}
	inline void findfac(ll n, int c) {
		if (n == 1) {
			return;
		}
		if (miller_rabin(n)) {
			fac[++tot] = n;
			return;
		}
		ll m = n;
		while (m == n) {
			m = pollard_rho(n, c--);
		}
		findfac(m, c);
		findfac(n / m, c);
	}
	inline int gao(ll _n) {
		n = _n;
		tot = 0;
		findfac(n, C);
		return tot; 
	}
}mill;
int main() {
	int f = 0, F = 0;
	ll n = 1e10;
	puts("{");
	for (ll i = 1; i <= n; ++i) {
		f = (f + mill.gao(i)) % mod;
		F = (F + f) % mod;
		if (i % S == 0) printf("%d,%d", f, F);  	
	}	
	puts("};");
	return 0;
}
