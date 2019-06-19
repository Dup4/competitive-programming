#include <bits/stdc++.h>
using namespace std;

#define ll long long
ll c, n;

int main() {
	while (scanf("%lld%lld", &c, &n) != EOF) {
		if (c > n) {
			puts("-1");
			continue;
		}
		ll x = n / c;
		ll res = c * c;
		if (x > 1) {
			res *= x * (x - 1);
		}
		printf("%lld\n", res);
	}
	return 0;
}
