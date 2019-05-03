#include <bits/stdc++.h>
using namespace std;

int n;
int G[11][11];
int f[11][11][11][11];
int Move[][2] = {
	{1, 0},
	{0, 1},
};

bool ok(int x, int y) {
	if (x < 1 || x > n || y < 1 || y > n) {
		return false;
	}
	return true;
}
int dp(int x, int y, int z, int w) {
	if (f[x][y][z][w] != -1) {
		return f[x][y][z][w];
	} 
	f[x][y][z][w] = 0;
	for (int i = 0; i < 2; ++i) {
		int nx = x + Move[i][0];
		int ny = y + Move[i][1];
		for (int j = 0; j < 2; ++j) {
			int nz = z + Move[j][0];
			int nw = w + Move[j][1];
			if (ok(nx, ny) && ok(nz, nw)) {
				f[x][y][z][w] = max(f[x][y][z][w], dp(nx, ny, nz, nw));
			}
		}
	}
	if (x == z && y == w) {
		f[x][y][z][w] += G[x][y];
	} else {
		f[x][y][z][w] += G[x][y] + G[z][w];
	}
	return f[x][y][z][w];
}

int main() {
	while (scanf("%d", &n) != EOF) {
		memset(G, 0, sizeof G);
		memset(f, -1, sizeof f);
		int x, y, d;
		while (scanf("%d%d%d", &x, &y, &d), x || y || d) {
			G[x][y] = d;
		}
	//	for (int i = 1; i <= n; ++i) {
	//		for (int j = 1; j <= n; ++j) {
	//			printf("%d%c", G[i][j], " \n"[j == n]);
	//		}
	//	}
		printf("%d\n", dp(1, 1, 1, 1));
	}
	return 0;
}
