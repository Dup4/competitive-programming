#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 5e5 + 10;
int n, k, a[N];
ll gao(int x) {
	ll s = 0;
	int need = k - (2 * x - k);
	for (int i = 1, j = need; i < j; ++i, --j) {
		s = max(s, 1ll * a[i] + a[j]);
	}
	for (int i = need + 1; i <= k; ++i)
		s = max(s, 1ll * a[i]);
	return s;
}

int main() {
	while (scanf("%d%d", &n, &k) != EOF) {
		memset(a, 0, sizeof a);
		for (int i = 1, x; i <= n; ++i) {
			scanf("%d", &x);
			++a[x];
		}
		sort(a + 1, a + 1 + k);
		ll res = 1e18;
		for (int i = (k + 1) / 2; i <= k; ++i) {
			res = min(res, 1ll * i * gao(i));
		}
		printf("%lld\n", res);
	}
	return 0;
}
