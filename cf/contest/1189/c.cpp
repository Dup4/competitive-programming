#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n, q, l, r, a[N], b[N];
int f[N][20], g[N][20];

int main() {
	while (scanf("%d", &n) != EOF) {
		memset(f, 0, sizeof f);
		memset(g, 0, sizeof g);
		for (int i = 1; i <= n; ++i) scanf("%d", a + i), b[i] = a[i];
		for (int j = 1; j <= 20; ++j) {
			for (int i = (1 << j); i <= n; i += (1 << j)) {
				int pre = (i - (1 << (j - 1))); 
				a[i] += a[pre];
				if (a[i] >= 10) {
					f[i][j] = 1;
					a[i] %= 10;
				}
			}
			for (int i = n; i >= 1; --i) f[i][j] += f[i + 1][j];
		}
		
		for (int i = 1; i <= n; ++i) a[i] = b[i];
		for (int j = 1; j <= 20; ++j) {
			for (int i = n - 1; i >= 1; i -= (1 << j)) {
				int pre = (i - (1 << (j - 1)));
				a[i] += a[pre];
				if (a[i] >= 10) {
					g[i][j] = 1;
					a[i] %= 10;
				}
			}
			for (int i = n; i >= 1; --i) g[i][j] += g[i + 1][j];
		}
		for (int j = 
		scanf("%d", &q);
		while (q--) {
			scanf("%d%d", &l, &r);
			
		}
	}
	return 0;
}
