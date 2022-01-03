#include <bits/stdc++.h>
using namespace std;

#define N 510
int n, m;
char G[N][N];

void clear(int x, int y, int dx, int dy) {
	if (x < 1 || x > n || y < 1 || y > m || G[x][y] == '.') {
		return;
	}
	G[x][y] = '.';
	clear(x + dx, y + dy, dx, dy);
}

bool empty() {
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (G[i][j] == '*') {
				return false;
			}
		}
	}
	return true;
}

bool work() {
	for (int i = 2; i < n; ++i) {
		for (int j = 2; j < m; ++j) {
			if (G[i][j] == '*' &&
				G[i - 1][j] == '*' &&
				G[i + 1][j] == '*' &&
				G[i][j - 1] == '*' &&
				G[i][j + 1] == '*') {
				clear(i, j - 1, 0, -1); 
			    clear(i, j + 1, 0, 1);
				clear(i - 1, j, -1, 0);
				clear(i + 1, j, 1, 0);
				G[i][j] = '.';
				return empty();
			}
		}
	}
	return false;
}

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%s", G[i] + 1);
		}
		puts(work() ? "YES" : "NO");
	}
	return 0;
}
