#include <bits/stdc++.h>
using namespace std;

#define N 100010
#define ll long long
int n, q, a[N], b[N];

ll f(int x) {
	ll res = 1e18;
	for (int i = 1; i <= n; ++i) {
		res = min(res, 1ll * (x - a[i]) * (x - a[i]) + b[i]);
	}
	return res;
}

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
		}
		for (int i = 1; i <= n; ++i) {
			scanf("%d", b + i);
		}
		int x;
		scanf("%d", &q);
		for (int i = 1; i <= q; ++i) {
			scanf("%d", &x);
			printf("%lld%c", f(x), " \n"[i == q]);
		}
	}
	return 0;
}
