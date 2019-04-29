#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
int n, a[N], b[N]; 
ll x, y, nx, ny;

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%lld%lld", &n, &x, &y);
		nx = ny = 0;
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			nx += 1ll * i * a[i];
			ny += 1ll * i * a[i] * a[i];
		}
		nx -= x;
		ny -= y;
		if (nx == 0 && ny == 0) {
			ll res = 0;
			for (int i = 1; i <= n; ++i) {
				res += b[a[i]];
				++b[a[i]];
			}
			printf("%lld\n", res);
			for (int i = 1; i <= n; ++i) {
				b[a[i]] = 0;
			}
		} else if (nx == 0 || ny == 0 || ny % nx) {
			puts("0");
		} else {
			int res = 0;
			for (int i = 1; i <= n; ++i) {
				ll aj = ny / nx - a[i];
				if (a[i] - aj == 0 || nx % (a[i] - aj)) {
					continue;
				}
				int j = i - nx / (a[i] - aj);
				if (j > i && j <= n && a[j] == aj) {
					++res;
				}
			}
			printf("%d\n", res);
		}
	}
	return 0;
}
