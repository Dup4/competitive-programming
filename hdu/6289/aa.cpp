#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 60
int n, m, k;
int a[N][N];
ll b[N], c[N];
ll g[N][N][N], h[N][N][N];
ll f[N][N][N][N];

bool cmp(int x, int y) {
	return x > y;
}
int main() {
	int _T; scanf("%d", &_T);
	while (_T--) {
		scanf("%d%d%d", &n, &m, &k);
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				scanf("%d", a[i] + j);
			}
		}
		memset(g, 0, sizeof g); 
		memset(h, 0, sizeof h);
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				b[j] = a[i][j];
				sort(b + 1, b + 1 + j, cmp);
				for (int o = 1; o <= j; ++o) { 
					c[o] = c[o - 1] + b[o];
					g[i][j][o] = c[o];
				}
			}
		}
		for (int j = 1; j <= m; ++j) {
			for (int i = 1; i <= n; ++i) {
				b[i] = a[i][j];
				sort(b + 1, b + 1 + i, cmp);
				for (int o = 1; o <= i; ++o) {
					c[o] = c[o - 1] + b[o]; 
					h[j][i][o] = c[o];
				}
			}
		}
		memset(f, -1, sizeof f); 
		f[1][1][0][0] = a[1][1];
		f[1][1][1][0] = 0;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				for (int o = 0; o <= k; ++o) {
					for (int l = 0; l <= k; ++l) {
						for (int q = l; q <= k; ++q) {
							if (f[i - 1][j][o][l] != -1) {
								f[i][j][o][q] = max(f[i][j][o][q], f[i - 1][j][o][l] + g[i][j - 1][q - l] + a[i][j]);
								f[i][j][o + 1][q] = max(f[i][j][o + 1][q], f[i - 1][j][o][l] + g[i][j - 1][q - l]); 
							}
							if (f[i][j - 1][o][l] != -1) {
								f[i][j][o][q] = max(f[i][j][o][q], f[i][j - 1][o][l] + h[j][i - 1][q - l] + a[i][j]);
								f[i][j][o + 1][q] = max(f[i][j][o + 1][q], f[i][j - 1][o][l] + h[j][i - 1][q - l]);
							}
						}
						if (f[i - 1][j][o][l] != -1) {
							f[i][j][o][l] = max(f[i][j][o][l], f[i - 1][j][o][l] + a[i][j]);  
						}
						if (f[i][j - 1][o][l] != -1) {
							f[i][j][o][l] = max(f[i][j][o][l], f[i][j - 1][o][l] + a[i][j]);  	
						}
					}
				}
			}
		}
		ll res = 0;
		for (int i = 0; i <= k; ++i) {
			res = max(res, f[n][m][i][i]);
		}
		printf("%lld\n", res);
	}
	return 0;
}
