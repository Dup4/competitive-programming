#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n, l, k;
char s[N], fa[N];
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
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= k; ++j) {
				int pos = max(i - l, 1);
				Min(f[i][j], f[pos][j - 1] + 1);

				f[i][j] = f[pre][j] + 1;
				int pre2 = max(pre - 1, 0);
				f[i][j] = min(f[i][j], f[pre2][j - 1] + 1);
				if (a[i] == a[pre]) {
					f[i][j] = min(f[i][j], f[pre][j - 1]);
					if (s[i] == s[pre2]) {
						f[i][j] = min(f[i][j], )
					}
					
				}
			}
		}
	}
	return 0;
}
