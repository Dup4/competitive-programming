#include <bits/stdc++.h>
using namespace std;

#define N 110
#define M 10010
int n, m, t, a[N][N], f[N][N], g[M], b[M];

int main() {
	while (scanf("%d%d%d", &n, &m, &t) != EOF) {
		memset(f, 0, sizeof f);
		memset(g, 0, sizeof g);
		b[0] = 0;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				scanf("%d", a[i] + j);
				b[++b[0]] = a[i][j];
			}
		}
		sort(b + 1, b + 1 + b[0]);
		b[0] = unique(b + 1, b + 1 + b[0]) - b - 1;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				a[i][j] = lower_bound(b + 1, b + 1 + b[0], a[i][j]) - b;
			}
		}
		int Maxx = 0;
		a[0][1] = 1e9, a[1][0] = 1e9; 
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				if (a[i - 1][j] == a[i][j]) f[i][j] = max(f[i][j], f[i - 1][j] + 1);
				if (a[i][j - 1] == a[i][j]) f[i][j] = max(f[i][j], f[i][j - 1] + 1);
				Maxx = max(Maxx, f[i][j]);	
			}
		}
		++Maxx;
		int limit = min(t, n * m / 2);
		for (int _ = 0; _ <= limit; ++_) {
			for (int i = 1; i <= n; ++i) {
				for (int j = 1; j <= m; ++j) {
					f[i][j] = g[a[i][j]] + 1;
					if (a[i - 1][j] <= a[i][j]) f[i][j] = max(f[i][j], f[i - 1][j] + 1);
					if (a[i][j - 1] <= a[i][j]) f[i][j] = max(f[i][j], f[i][j - 1] + 1); 
				}	
			}
			for (int i = 1; i <= n; ++i) {
				for (int j = 1; j <= m; ++j) {
					g[a[i][j]] = max(g[a[i][j]], f[i][j]);
				}
			}
			for (int i = 2; i <= b[0]; ++i) {
				g[i] = max(g[i], g[i - 1]);
			}
		}
		int Max = 0;
		for (int i = 1; i <= b[0]; ++i) {
			Max = max(Max, g[i]);
		}
		printf("%lld\n", 1ll * (t - limit) * Maxx + Max);
	}
	return 0;
}
