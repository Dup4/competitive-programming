#include <bits/stdc++.h>
using namespace std;

#define N 1000010
#define INF 0x3f3f3f3f
int n, m, f[N][3], g[N][3], nx[3];
char s[N], t[N];
int vis[N];

bool ok() {
	m = 0;
	for (int i = 1; i <= n; ++i) if (vis[i]) {
		t[++m] = s[i]; 
	}
	t[m + 1] = 0;
	if (m >= n / 2) {
		printf("%s\n", t + 1);
		return 1;
	}
	return 0;
}

int main() {
	while (scanf("%s", s + 1) != EOF) {
		n = strlen(s + 1);
		for (int i = 1; i <= n; ++i) vis[i] = 0;
		nx[0] = nx[1] = nx[2] = 0;
		for (int i = 1; i <= n + 1; ++i) {
			for (int j = 0; j < 3; ++j) {
				g[i][j] = nx[j];
			}
			if (i <= n) {
				nx[s[i] - 'a'] = i;
			}
		}
		nx[0] = nx[1] = nx[2] = n + 1;
		for (int i = n; i >= 0; --i) {
			for (int j = 0; j < 3; ++j) {
				f[i][j] = nx[j];
			}
			if (i > 0) {
				nx[s[i] - 'a'] = i;
			}
		}
		int l = 0, r = n + 1;
		while (l <= r) {
			int Min = INF, pos = -1;
			for (int i = 0; i < 3; ++i) {
				if (f[l][i] < g[r][i] && f[l][i] - l + r - g[r][i] < Min) {
					Min = f[l][i] - l + r - g[r][i];
					pos = i;
				}
			}
			if (pos == -1) break;
			l = f[l][pos];
			r = g[r][pos];
			vis[l] = vis[r] = 1;
		}
		if (l < r - 1) {
			vis[l + 1] = 1;
		}
		if (!ok()) printf("IMPOSSIBLE\n");
	}
	return 0;
}
