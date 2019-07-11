#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n, m;
int vis[N][2];

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		memset(vis, 0, sizeof vis);
		for (int i = 1, x, y; i <= m; ++i) {
			scanf("%d%d", &x, &y);
			vis[x][0] = 1;
			vis[y][1] = 1;
		}
		int ans = 0;
		if (n & 1) {
			if (vis[n / 2 + 1][0] == 0 && vis[n / 2 + 1][1] == 0) {
				++ans;
				vis[n / 2 + 1][0] = 1;
				vis[n / 2 + 1][1] = 1;
			}
		}
		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j < 2; ++j) {
				ans += (vis[i][j] == 0);
			}
		}
		printf("%d\n", ans);	
	}
	return 0;
}
