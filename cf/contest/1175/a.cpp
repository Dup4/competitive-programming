#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		ll res = 0, n, k;
		scanf("%lld%lld", &n, &k);
		while (n) {
			if (n % k == 0) {
				++res;
				n /= k;
			} else {
				res += n % k;
				n -= n % k;
			}
		}
		printf("%lld\n", res);
	}
	return 0;
}
