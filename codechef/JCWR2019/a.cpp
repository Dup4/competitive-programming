#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pli pair <ll, int>
#define fi first
#define se second
const int N = 2e6 + 10;
const ll INF = 0x3f3f3f3f3f3f3f3f;
int T, n, k, a[N];
pli g[2]; 
ll f[N];

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &k);
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		g[0] = g[1] = pli(-INF, -1);
		ll res = 0;
		for (int i = 1; i <= n; ++i) {
			f[i] = a[i]; 
			if (g[0].se == i - k) {
				f[i] = max(f[i], g[1].fi + a[i]);
			} else {
				f[i] = max(f[i], g[0].fi + a[i]);
			}
			res = max(res, f[i]);
			if (i % k == 0) {
				for (int j = i - k + 1; j <= i; ++j) {
					pli now = pli(f[j], j);
					if (now > g[0]) {
						g[1] = g[0];
						g[0] = now;
					} else if (now > g[1]) {
						g[1] = now;
					}
				}
			}
		}	
		printf("%lld\n", res);	
	}
	return 0;
}
