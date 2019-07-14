#include <bits/stdc++.h>
using namespace std;

#define ll long long
ll l, r;

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%lld%lld", &l, &r);
		if (l == r) {
			printf("%lld %lld %lld %lld\n", l, l, l, l);
		} else {
			printf("%lld %lld %lld %lld\n", (r * (r - 1)), l, r, 1ll);
		}
	}
	return 0;
}
