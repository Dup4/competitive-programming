#include <bits/stdc++.h>
using namespace std;

const int N = 110;
int a[N][N], b[N][N], n, m, res;
int Move[][2] = {
	{-1, 0},
	{1, 0},
	{0, -1},
	{0, 1}
};
bool ok(int x, int y) {
	if (x < 1 || x > n || y < 1 || y > m) return false;
	return true;
}
bool check() {
	memset(b, 0, sizeof b);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			for (int k = 0; k < 4; ++k) {
				int nx = i + Move[k][0];
				int ny = j + Move[k][1];
				if (ok(nx, ny) && a[i][j] == a[nx][ny])
					++b[i][j];
				if (b[i][j] > 1) return false;
			}
		}
	}
	return true;
}

void dfs(int x, int y) {
	if (x > n) {
		res += check();
		return;
	}
	for (int i = 0; i < 2; ++i) {
		a[x][y] = i;
		if (y == m) dfs(x + 1, 1);
		else dfs(x, y + 1);
	}
}

int main() {
	res = 0;
	cin >> n >> m;
	dfs(1, 1);
	cout << res << endl;
	return 0;
}
