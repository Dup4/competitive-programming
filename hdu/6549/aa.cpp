#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n, l, k;
char s[N];
int fa[N];
int f[N][12];

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
		f[1][1] = 0;   
		for (int i = 2; i <= n; ++i) {
			for (int j = 1; j <= k; ++j) {
				int pos = max(i - l - 1, 1);
				Min(f[i][j], f[pos][j - 1] + 1);
				if (fa[pos] == fa[i]) {
					Min(f[i][j], f[pos][j]);
				}
				if (fa[pos + 1] == fa[i]) {
					Min(f[i][j], f[pos][j - 1]);
				}
			}
		}		
		printf("%d\n", f[n][k]);
	}
	return 0;
}
