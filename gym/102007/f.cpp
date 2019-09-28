#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
int n, m, p[N], c[N];
bool check(ll x) {
	ll res = 0;
	for (int i = 1; i <= n; ++i) {
		ll t = 1ll * p[i] * x - c[i];
		res += max(0ll, t);
		if (res >= m) return true;
	}
	return res >= m;
}

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%d%d", p + i, c + i);
		ll l = 0, r = 2e9, res = 2e9;
		while (r - l >= 0) {
			ll mid = (l + r) >> 1;
			if (check(mid)) {
				r = mid - 1;
				res = mid;
			} else {
				l = mid + 1;
			}
		}
		printf("%lld\n", res);
	}
	return 0;
}
