#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll p = 998244353;

ll inv2, inv6;

ll qpow(ll x, ll n) {
	ll res = 1;
	while (n) {
		if (n & 1) res = res * x % p;
		x = x * x % p;
		n >>= 1;
	}
	return res;
}

ll n;

ll f1(ll x) {
	x %= p;
	return x * (x + 1) % p * inv2 % p;
}

ll f2(ll x) {
	x %= p;
	return x * (x + 1) % p * (2 * x % p + 1) % p * inv6 % p;;
}

int main() {
	inv2 = qpow(2, p - 2);
	inv6 = qpow(6, p - 2);
	while (scanf("%lld", &n) != EOF) {
		ll limit = sqrt(n) + 1;
		ll res = 0;
		for (int i = 2; i <= limit; ++i) {
			ll a = i;
			ll t = 1, tmp = a;
			while (tmp <= n) {
				t++;
				tmp *= a;
			}
			--t;
			res = (res + (a * n % p * t % p - (qpow(a, t + 2) - a * a % p + p) % p * qpow(a - 1, p - 2) % p) % p + p) % p;
			res = (res + a * t % p) % p;
		}
		ll other = (n + 1) % p * (f1(n) - f1(limit) + p) % p - (f2(n) - f2(limit) + p);
		other = (other % p + p) % p;
		res = (res + other) % p;
		res = (res % p + p) % p;
		printf("%lld\n", res);
	}
	return 0;
}
