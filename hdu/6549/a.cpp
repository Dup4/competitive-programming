#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n, l, k;
char s[N], fa[N];
int f[N][15];

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
		f[0][0] = 0;
		for (int i = 1; i <= n; ++i) {
			int pre = max(i - l, 0);
			for (int j = 1; j <= k; ++j) {
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
