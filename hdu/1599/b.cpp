#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 310;
const ll INF = 0x3f3f3f3f3f3f;
int n, m; ll f[N][N], g[N][N];
ll floyd() {
	ll res = INF;
	for (int k = 1; k <= n; ++k) {
		for (int i = 1; i < k; ++i) {
			for (int j = i + 1; j < k; ++j) {
					res = min(res, f[i][j] + g[i][k] + g[k][j]);
			}
		}
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
	}
	return res;
}

int main() {
	while (scanf("%d%d", &n, &m) != EOF) { 
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j) {
				f[i][j] = g[i][j] = INF;
			}
		for (int i = 1, u, v, w; i <= m; ++i) {
			scanf("%d%d%d", &u, &v, &w);
			f[u][v] = f[v][u] = g[u][v] = g[v][u] = min(f[u][v], 1ll * w);
		}
		ll res = floyd();
		if (res >= INF) puts("It's impossible.");
		else printf("%lld\n", res);
	}
	return 0;
}
