#include <bits/stdc++.h>
using namespace std;

#define N 1010
int n, m, q;
int G[N][N];

bool f(int x, int y) {
	if (x < 1 || x > n || y < 1 || y > m || G[x][y]) {
		return false;
	}
	return true;
}

bool ok(int x, int y) {
	return (f(x, y) && f(x + 1, y) && f(x, y + 1) && f(x + 1, y + 1));
}

int main() {
	while (scanf("%d%d%d", &n, &m, &q) != EOF) {
		memset(G, 0, sizeof G);
		int res = 0;
		for (int i = 1; i < n; ++i) {
			for (int j = 1; j < m; ++j) {
				if (G[i][j] == 0 && G[i + 1][j] == 0 && G[i][j + 1] == 0 && G[i + 1][j + 1] == 0) {
					++res;
				}
			}
		}
		for (int i = 1, x, y; i <= q; ++i) {
			scanf("%d%d", &x, &y);
			res -= ok(x - 1, y - 1);
			res -= ok(x - 1, y);
			res -= ok(x, y - 1);
			res -= ok(x, y);
			G[x][y] = 1;
			printf("%d\n", res);
		}
	}
	return 0;
}
