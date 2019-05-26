#include <bits/stdc++.h>
using namespace std;

#define ll long long
const ll p = 332748118;
ll x[2], y[2];

ll f(ll a1, ll n, ll d) {
	a1 %= p;
	n %= p;
	d %= p;
	return (a1 % p * n % p + (1ll * n * (n - 1) / 2) % p * d % p) % p;
}

int main() {
	while (scanf("%lld%lld%lld%lld", x, x + 1, y, y + 1) != EOF) {
		printf("%lld\n", 2ll * f(f(x[0] + y[0] - 1, x[1] - x[0] + 1, 1), y[1] - y[0] + 1, x[1] - x[0] + 1) % p);
	}
	return 0;
}
