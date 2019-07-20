#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll p = (ll)1e9 + 7;

ll qpow(ll x, ll n) {
	ll res = 1;
	while (n) {
		if (n & 1) {
			res = res * x % p; 
		}
		x = x * x % p;
		n >>= 1;
	}
	return res;
}

int n, m;

int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		scanf("%d %d", &n, &m);
		if (n == 1) {
			puts("1");
			continue;
		} else if (m == 0) {
			puts("0");
			continue;
		}
		printf("%lld\n", 1ll * qpow(n - 1, p - 2));
	}
	return 0;
}
