#include <bits/stdc++.h>
using namespace std;

#define N 300010
#define D 20
int n, q;
int a[N];
int f[N][D], last[D];

int main() {
	while (scanf("%d%d", &n, &q) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
		}
		for (int i = 0; i < D; ++i) {
			f[n + 1][i] = n + 1;
			last[i] = n + 1;
		}
		for (int i = n; i >= 1; --i) {
			for (int j = 0; j < D; ++j) {
				f[i][j] = n + 1; 
			}
			for (int j = 0; j < D; ++j) {
				if ((a[i] >> j) & 1) {
					for (int k = 0; k < D; ++k) {
						f[i][k] = min(f[i][k], f[last[j]][k]);
					}
					last[j] = i;
					f[i][j] = i;
				}
			}
		}
		for (int i = 1, x, y; i <= q; ++i) {
			scanf("%d%d", &x, &y);
			bool F = 0;
			for (int j = 0; j < D; ++j) {
				if ((a[y] >> j) & 1) {
					F |= (f[x][j] <= y);
				}
			}
			puts(F ? "Shi" : "Fou");
		}
	}
	return 0;
}
