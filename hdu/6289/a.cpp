#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 60
int n, m, k;
int a[N][N];
ll f[N][N][N][N];
int Move[][2] = {
	{-1, 0},
	{0, -1},
};
bool ok(int x, int y) {
	if (x < 1 || x > n || y < 1 || y > m) {
		return false;
	}
	return true;
}

int main() {
	int _T; scanf("%d", &_T);
	while (_T--) {
		memset(f, 0, sizeof f);
		scanf("%d%d%d", &n, &m, &k);
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				scanf("%d", a[i] + j);
			}
		}
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				for (int o = 1; o <= k; ++o) {
					for (int l = 1; l <= k; ++l) {
						for (int q = 0; q < 2; ++q) {
							int x = i + Move[q][0];
							int y = j + Move[q][1]; 
							if (ok(x, y)) {
								f[i][j][o][l] = max(f[i][j][o][l], f[x][y][o - 1][l]);
								f[i][j][o][l] = max(f[i][j][o][l], f[x][y][o - 1][l - 1] + a[x][y] + )
							}
						}
					}
				}
			}
		}
	}
	return 0;
}
