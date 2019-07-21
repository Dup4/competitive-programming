#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n, l, k;
char s[N];
int fa[N];
int f[N][15];

void Min(int &x, int y) {
	if (x > y) x = y;
}

int main() {
	while (scanf("%d%d%d", &n, &l, &k) != EOF) {
		k = min(n, k);
		scanf("%s", s + 1);
		int tot = 0;
		fa[1] = ++tot;
		for (int i = 2; i <= n; ++i) {
			if (s[i] == s[i - 1]) {
				fa[i] = fa[i - 1];
			} else {
				fa[i] = ++tot;
			}
		}
		memset(f, 0x3f, sizeof f);
		f[1][1] = 0;
		for (int i = 2; i <= n; ++i) {
			for (int j = 1; j <= k; ++j) {
				int pos = max(i - l, 1);
				//将[pos + 1, i]染成同一种颜色
				Min(f[i][j], f[pos][j - 1] + 1);
				//将[pos + 1, i]染成和s[pos]的颜色一样
				Min(f[i][j], f[pos][j] + 1);
				if (fa[i] == fa[pos + 1]) {
				    Min(f[i][j], f[pos][j - 1]);	
					int pos2 = max(pos - 1, 1);
					if (s[i] == s[pos2]) {
						//考虑此时f[pos][j]这个状态下的颜色要么是任意的，要么和前面一个位置的颜色一样
						//如果是任意的，可以任意的，可以直接合并
						//如果和前面一个位置的颜色一样，也可以直接合并
						Min(f[i][j], f[pos][j]);
					}
				}
			}
		}
		printf("%d\n", f[n][k]);
	}
	return 0;
}
