#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 110
int n, m;
ll C(int n, int m) {
	ll res = 1;
	for (int i = n; i > n - m; --i) {
		res *= i;
	}
	for (int i = 1; i <= m; ++i) {
		res /= i;
	}
	return res;
}

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%*s");
		}
		ll res = C(n + 1, 2) * C(m + 1, 2);
		res += C(res, 2);
		res -= 2ll * (C(n + 1, 2) * C(m + 1, 4) + C(n + 1, 4) * C(m + 1, 2));
		res -= 12ll * C(n + 1, 3) * C(m + 1, 3);
		res -= (n + m - 2) * C(n + 1, 2) * C(m + 1, 2);
		printf("%lld\n", res + 1);
	}
	return 0;
}
