#include <bits/stdc++.h>
using namespace std;

#define N 100010
#define D 20
int n, q, l, r, a[N];
int f[N][20], g[N][20];

int main() {
	while (scanf("%d", &n) != EOF) {
		memset(f, 0, sizeof f);
		memset(g, 0, sizeof g);
		for (int i = 1; i <= n; ++i) scanf("%d", a + i), g[i][0] = a[i]; 
		for (int j = 1; j <= 20; ++j) {
			for (int i = 1; i <= n; ++i) {
				if (i + (1 << j) - 1 > n) break;
				int nx = (i + (1 << (j - 1)));
				f[i][j] = f[i][j - 1] + f[nx][j - 1];
				g[i][j] = g[i][j - 1] + g[nx][j - 1];
				if (g[i][j] >= 10) {
					++f[i][j];
					g[i][j] %= 10;
				}
			}
		}
		scanf("%d", &q);
		while (q--) {
			scanf("%d%d", &l, &r);
			int t = r - l + 1, q = 0;
			while (t) {
				++q;
				t /= 2;
			}
			--q;
			printf("%d\n", f[l][q]);
		}
	}
	return 0;
}
