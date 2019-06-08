#include <bits/stdc++.h>
using namespace std;

#define N 110
#define ll long long
const ll p = 1e9 + 7;
int n, a[N];
void add(ll &x, ll y) {
	x += y;
	if (x >= p) {
		x -= p;
	}
}
ll f(int l, int r) {
	ll res = 0;
	int Max = 0;
	for (int i = l; i <= r; ++i) {
		Max = max(Max, a[i]);
		res = max(res, 1ll * Max * (r - i + 1)); 
	}
	return res % p;
}

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
		}
		ll res = 0;
		for (int i = 1; i <= n; ++i) {
			for (int j = i; j <= n; ++j) {
				add(res, f(i, j));
			}
		}
		printf("%lld\n", res);
	}
	return 0;
}
