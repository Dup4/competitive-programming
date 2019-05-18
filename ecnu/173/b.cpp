#include <bits/stdc++.h>

using namespace std;

int main() {
	int n, i, j, k;
	char f[105][105];
	int p[27 * 27 * 27];
	scanf("%d", &n);
	n++;
	memset(p, 0, sizeof p);
	for (i = 1; i <= n; ++i) {
		for (j = 1; j <= i; ++j)
			scanf(" %c", &f[i][j]);
	}
	char a, b, c, t;
	int ans = 0;
	for (i = 1; i < n; ++i)
		for (j = 1; j <= i; ++j)
			for (k = 1; k <= n - i; ++k) {
				a = f[i][j]; b = f[i + k][j]; c = f[i + k][j + k];
				if (a > b) {
					t = a; a = b; b = t;
				}
				if (a > c) {
					t = a; a = c; c = t;
				}
				if (b > c) {
					t = b; b = c; c = t;
				}
				int q = (a - 97) * 26 * 26 + (b - 97) * 26 + (c - 97);
				if (p[q] == 0) {
					++ans;
					p[q] = 1;
				}
				if (j + k <= i) {
					a = f[i][j]; b = f[i][j + k]; c = f[i + k][j + k];
					if (a > b) { t = a; a = b; b = t;}
					if (a > c) { t = a; a = c; c = t;}
					if (b > c) { t = b; b = c; c = t;}
					int q = (a - 97) * 26 * 26 + (b - 97) * 26 + (c - 97);
					if (p[q] == 0) {
						++ans;
						p[q] = 1;
					}
				}
			}
	printf("%d\n", ans);
	return 0;
}
