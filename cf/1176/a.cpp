#include <bits/stdc++.h>
using namespace std;

#define ll long long
int solve(ll n) {
	int res = 0;
	while (n > 1) {
		++res;
		if (n % 2 == 0) {
			n /= 2;
		} else if (n % 3 == 0) {
			n /= 3;
			n *= 2;
		} else if (n % 5 == 0) {
			n /= 5;
			n *= 4;
		} else {
			return -1;
		}
	}
	return res;
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		ll n; scanf("%lld", &n);
		printf("%d\n", solve(n));
	}
	return 0;
}
