#include <bits/stdc++.h>
using namespace std;

#define ll long long
const ll mod = 1e9 + 7;
int T, n, odd, even, other;
ll qmod(ll base, ll n) {
	ll res = 1;
	while (n) {
		if (n & 1) res = res * base % mod;
		base = base * base % mod;
		n >>= 1;
	}
	return res;
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		odd = 0; even = 0; other = 0;
		for (int i = 1, x, y; i <= n; ++i) {
			scanf("%d%d", &x, &y);
			if (x % 2 != y % 2) ++other;
			else if (x % 2 == 1) ++odd;
			else ++even;
		}		
		if (other > 0) printf("%lld\n", qmod(2, n - 1));
		else if (odd % 2 == 0) puts("0");
		else printf("%lld\n", qmod(2, n));
	}
	return 0;
}
