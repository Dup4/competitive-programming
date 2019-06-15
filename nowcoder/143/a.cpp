#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define db double
#define N 100010
#define pii pair <int, int>
#define fi first
#define se second
int n, k; pii a[N];

int main() {
	while (scanf("%d%d", &n, &k) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &a[i].fi);
		}
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &a[i].se);
			a[i].se *= a[i].fi;
		}
		sort(a + 1, a + 1 + n, [&](pii x, pii y){
			if (x.se != y.se) {
				return x.se > y.se;
			}		
			return x.fi < y.fi;
		});
		db res = 0;
		ll x = 0, y = 0;
		for (int i = 1; i <= n; ++i) {
			x += a[i].se;
			y += a[i].fi;
			if (i >= n - k) {
				res = max(res, x * 1.0 / y);
			}
		}
		printf("%.10f\n", res);
	}
	return 0;
}
