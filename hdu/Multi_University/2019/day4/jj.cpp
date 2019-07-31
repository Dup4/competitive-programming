#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long u64;
typedef __int128_t i128;
typedef __uint128_t u128;
ll n;
ll fac[220]; int tot;
const int C = 1000;
const int S = 5;
//64位大整数随机数 
mt19937_64 rd(time(0));
ll gcd(ll a, ll b) {
	return b ? gcd(b, a % b) : a;
}


		mod = m; assert(mod & 1);
		inv = m; for (int i = 0; i < 5; ++i) inv *= 2 - inv * m;
		r2 = -u128(m) % m;
	}
	static u64 reduce(u128 x) {
		u64 y = u64(x >> 64) - u64((u128(u64(x)*inv)*mod) >> 64);
		return ll(y)<0 ? y + mod : y;
	}
	Mod64& operator += (Mod64 rhs) { n_ += rhs.n_ - mod; if (ll(n_)<0) n_ += mod; return *this; }
	Mod64 operator + (Mod64 rhs) const { return Mod64(*this) += rhs; }
	Mod64& operator -= (Mod64 rhs) { n_ -= rhs.n_; if (ll(n_)<0) n_ += mod; return *this; }
	Mod64 operator - (Mod64 rhs) const { return Mod64(*this) -= rhs; }
	Mod64& operator *= (Mod64 rhs) { n_ = reduce(u128(n_)*rhs.n_); return *this; }
	Mod64 operator * (Mod64 rhs) const { return Mod64(*this) *= rhs; }
	u64 get() const { return reduce(n_); }
	static u64 mod, inv, r2;
	u64 n_;
};
u64 Mod64::mod, Mod64::inv, Mod64::r2;

ll mul(ll a, ll b, ll p) {
	Mod64::set_mod(p);
	Mod64 A(a), B(b);
	return (A * B).get();
}
ll qmod(ll base, ll n, ll p) {
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
bool check(ll a, ll n) {
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
bool miller_rabin(ll n) {
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
ll pollard_rho(ll n, int c) {
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
void findfac(ll n, int c) {
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

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%lld", &n);
		tot = 0;
		findfac(n, C);
	//    sort(fac + 1, fac + 1 + tot); 	
		int res = 1e9;
		int tmp = 1;
		for (int i = 2; i <= tot; ++i) {
			if (fac[i] != fac[i - 1]) {
				res = min(res, tmp);
				tmp = 1;	
			} else {
				++tmp;
			}
		}
		res = min(res, tmp);
		printf("%d\n", res);
	}
	return 0;
}
