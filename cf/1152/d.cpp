#include <bits/stdc++.h>
using namespace std;

#define ll long long
const ll p = (ll)1e9 + 7;

int main() {
	int n;
	while (scanf("%d", &n) != EOF) {
		ll res = 1;
		for (int i = 2; i <= n; ++i) {
			res = (res * 3) % p;
		}
		printf("%lld\n", res);
	}
	return 0;
}
