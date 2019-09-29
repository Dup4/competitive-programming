#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll mod = 1e9 + 7;
ll f(ll x) {
	ll res = 1;
	while (x) {
		res = res * (x % 10) % mod;
		x /= 10;
	}
	return res;
}

int main() {
	int _T; cin >> _T;
	while (_T--) {
		ll l, r;
		scanf("%lld%lld", &l, &r);
		ll res = 1;
		for (ll i = l; i <= r; ++i) {
			res = res * f(i) % mod;
			if (!res) break;
		}
		printf("%lld\n", res);
	}
	return 0;
}
