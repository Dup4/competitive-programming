#include <bits/stdc++.h>
using namespace std;

#define ll long long
const ll p = 998244353;

ll qmod (ll base, ll n) {
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

int main() {
	int n, m;
	while (scanf("%d%d", &n, &m) != EOF) {
		printf("%lld\n", qmod(2, n - 1) * qmod(2, m - 1) % p * 4 % p);
	}
	return 0;
}
