#include <bits/stdc++.h>
using namespace std;

#define N 110
int n, m;
char G[N][N];
int Move[][2] = {
	{-1, 0},
	{1, 0},
	{0, -1},
	{0, 1},
};
bool ok(int x, int y) {
	if (x < 1 || x > n || y < 1 || y > m || G[x][y] == '#') {
		return false;
	}
	return true;
}

void DFS(int x, int y) {
	G[x][y] = '#';
	for (int i = 0; i < 4; ++i) {
		int nx = x + Move[i][0];
		int ny = y + Move[i][1];
		if (ok(nx, ny)) {
			DFS(nx, ny);
		}
	}
}

int main() {
	int T = 0;
	while (scanf("%d%d", &n, &m) != EOF) {
		printf("Case %d: ", ++T);
		for (int i = 1; i <= n; ++i) {
			scanf("%s", G[i] + 1);
		}
		int res = 0;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				if (G[i][j] == '-') {
					++res;
					DFS(i, j);
				}
			}
		}
		printf("%d\n", res);
	}	
	return 0;
}
