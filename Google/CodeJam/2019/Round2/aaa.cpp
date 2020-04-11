#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 510
#define pll pair <ll, ll>
#define fi first
#define se second
#define db double
int n, m;
pll a[N];
ll b[N];
int cnt[2];
struct node {
	ll x, y;
	node () {}
	node (ll x, ll y) : x(x), y(y) {}
	bool operator < (const node &other) const {
		return x * other.y < y * other.x;
	}
}c[N];

bool ok() {
	m = 0;
	cnt[0] = 0;
	cnt[1] = 0;
	for (int i = 2; i <= n; ++i) {
		ll x = a[i].fi - a[i - 1].fi;
		ll y = a[i].se - a[i - 1].se;
		if (x <= 0 && y <= 0) {
			return false; 
		}
		if (x < 0 || y < 0) { 
			c[++m] = node(x, y);
			if (x > 0) {
				++cnt[0];
			} else {
				++cnt[1];
			}
		}
	}
	node Max = node(-1e9, 1), Min = node(1e9, 1);
	for (int i = 1; i <= m; ++i) {
		if (c[i].x < 0) {
			Min = min(Min, node(-c[i].x, c[i].y)); 
		} else {
			Max = max(Max, node(c[i].x, -c[i].y));
		}
	}
	return Max < Min;
}

int main() {
	int T; scanf("%d", &T);
	for (int kase = 1; kase <= T; ++kase) {
		printf("Case #%d: ", kase);
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			scanf("%lld%lld", &a[i].fi, &a[i].se);
		}
		sort(a + 1, a + 1 + n);
		int res = 0;
		do {
			if (ok()) {
				++res;
			}
		} while (next_permutation(a + 1, a + 1 + n));
		printf("%d\n", res);
	}
	return 0;
}
