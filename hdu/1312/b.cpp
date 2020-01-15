#include <bits/stdc++.h>
using namespace std;
const int N = 1e2 + 10;
int n, m;
char s[N][N]; int use[N][N];

int Move[4][2] = {
	{-1, 0},
	{1, 0},
	{0, -1},
	{0, 1},
};

bool ok(int x, int y) {
	if (x < 1 || x > n || y < 1 || y > m)
		return false;
	if (s[x][y] == '#')
		return false;
	if (use[x][y] == 1)
		return false;
	return true;
}

void dfs(int x, int y) {
	if (s[x][y] == '#') 
		return;
	if (use[x][y])
		return;
	use[x][y] = 1;
	for (int i = 0; i < 4; ++i) {
		int nx = x + Move[i][0];
		int ny = y + Move[i][1];
		if (ok(nx, ny))
			dfs(nx, ny);
	}
}

int main() {
	while (scanf("%d%d", &m, &n), n + m) {
		memset(use, 0, sizeof use);
		for (int i = 1; i <= n; ++i)
			scanf("%s", s[i] + 1);
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j)
				if (s[i][j] == '@')
					dfs(i, j);
		int res = 0;
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j)
				res += use[i][j];
		printf("%d\n", res);
	}
	return 0;
}
