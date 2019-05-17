#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 1010
int n, m, a[N], b[N];
int G[N][N], f[N][N];
ll L, R;

int main() {
	while (scanf("%d%d%lld%lld", &n, &m, &L, &R) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
		}
		for (int i = 1; i <= m; ++i) {
			scanf("%d", b + i);
		}
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				ll x = 1ll * a[i] * b[j];
				G[i][j] = (x < L || x > R);
			}
		}
		for (int i = 1; i <= n; ++i) {
			int nx = m + 1;
			for (int j = m; j >= 1; --j) {
				f[i][j] = nx;
				if (G[i][j]) {
					nx = j;
				}
			}
		}
		ll res = 0;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				int now = f[i][j];
				for (int k = i; k <= n; ++k) {
					now = min(now, f[k][j]);
					res += now - j;
				}
			}
		}
		printf("%lld\n", res);
	}
	return 0;
}
