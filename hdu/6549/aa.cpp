#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n, l, k;
char s[N];
int fa[N];
int f[N][12][2];
// f[i][j][0] 表示到第i位，划分成j段，最后一段的颜色固定的最小代价
// f[i][j][1] 表示到第i位，划分成j段，最后一段的颜色任意并且不算入j的最小代价

void Min(int &x, int y) {
	if (y <= x) x = y;
}

int main() {
	while (scanf("%d%d%d", &n, &l, &k) != EOF) {
		Min(k, n);
		scanf("%s", s + 1);
		for (int i = 1; i <= n; ++i) {
			if (i == 1 || s[i] != s[i - 1]) {
				fa[i] = i;
			} else {
				fa[i] = fa[i - 1];
			}
		}
		memset(f, 0x3f, sizeof f);
		for (int i = 0; i < 12; ++i) 
			for (int j = 0; j < 2; ++j)
				f[0][i][j] = 0;
		f[1][0][1] = 1;
		f[1][1][0] = 0;   
		for (int i = 2; i <= n; ++i) {
			for (int j = 0; j <= k; ++j) {
				int pos = max(i - l - 1, 0);
				if (j) Min(f[i][j][0], f[pos][j - 1][0] + 1);
				if (j) Min(f[i][j][0], f[pos][j - 1][1] + 1);
				pos = max(i - l, 0);
				Min(f[i][j][0], f[pos][j][0] + 1);
				if (j) Min(f[i][j][0], f[pos][j - 1][1] + 1);
				Min(f[i][j][1], f[pos][j][1] + 1);
				if (j) Min(f[i][j][1], f[pos][j][0] + 1);
				pos = max(fa[i] - 1, 0);
				if (j) Min(f[i][j][0], f[pos][j - 1][0]);
				if (j) Min(f[i][j][0], f[pos][j - 1][1]);
			}
		}		
		int res = min(f[n][0][1], f[n][k][0]);
		for (int i = 1; i < k; ++i) {
			Min(res, f[n][i][0]);
			Min(res, f[n][i][1]);
		}
		printf("%d\n", res);
	}
	return 0;
}
