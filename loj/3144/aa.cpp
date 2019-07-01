#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 1000010
#define pll pair <ll, ll> 
#define fi first
#define se second
int n;
ll l[N], r[N];	
ll A, B;
ll gcd(ll a, ll b) {
	return b ? gcd(b, a % b) : a; 
}

int main() {
	while (scanf("%d%lld%lld", &n, &A, &B) != EOF) {
		ll sum = 0;
		for (int i = 1; i <= n; ++i) {
			scanf("%lld%lld", l + i, r + i);
			sum += r[i] - l[i] + 1;
		}
		ll g = gcd(a, b + 1);
		if (1.0 * A * B / g > 1e18) {
			printf("%lld\n", sum);
			continue;
		}
		multiset <pll> se; 
		ll res = 0;
		ll T = A / g * B;
		for (int i = 1; i <= n; ++i) {
			l[i] %= T;
			r[i] %= T;
			se.insert(pll(l[i], 1));
			se.insert(pll(r[i], 0)); 
			se.insert(pll(r[i] + 1, -1));
		}
		ll base = 0, x = -1e18;
		auto it = se.begin();
		while (1) {
			if (base == 0 && it == se.end()) {
				break;
			}
			if (base == 0) {
				x = *it.fi;
			}
			while (it != se.end() && *it.fi <= x) {
				
			}
		}
		printf("%lld\n", res); 
	}
	return 0;
}
