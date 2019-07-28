#include <bits/stdc++.h>
using namespace std;

#define ll long long
ll n, p;

void solve() {
	ll res = 1;
	for (int i = 1; i <= n; ++i) {
		res *= i;
		if (res >= p) {
			puts("0");
			return;
		}
	}
	ll res2 = 1;
	for (int i = 1; i <= res; ++i) {
		res2 *= i;
		if (res2 >= p) {
			puts("0");
			return;
		}
	}
	ll res3 = 1;
	for (int i = 1; i <= res2; ++i) {
		res3 = res3 * i % p;
	}
	printf("%lld\n", res3);
}

int main() {
	while (scanf("%lld%lld", &n, &p) != EOF) {
		solve();
	}
	return 0;
}
