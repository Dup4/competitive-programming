#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 1e6 + 10;

ll n, q, p;

ll qpow(ll x, ll n) {
	ll res = 1;
	ll tmp = x % p;
	while (n) {
		if (n & 1) res = res * tmp % p;
		tmp = tmp * tmp % p;
		n >>= 1;
	}
	return res;
}

ll sum(ll q, ll n) {
	if (q == 0) return 0;
	if (n == 0) return 1;
	if (n & 1) {
		return ((1 + qpow(q, n / 2 + 1)) % p * sum(q, n / 2) % p) % p;
	} else {
		return ((1 + qpow(q, n / 2 + 1)) % p * sum(q, n / 2 - 1) + qpow(q, n / 2) % p) % p;
	}
}

ll solve(ll A, ll B) {
	ll ans = sum(A, B) - 1;
	while(ans < p) ans += p;
	ans %= p;
	return ans;
}

int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		scanf("%lld %lld %lld", &q, &n, &p);
		printf("%lld\n", solve(q, n));
	}	
	return 0;
}
