#include <bits/stdc++.h>
using namespace std;

#define N 110
int n;
char G[N][N];
int Move[][2] = {
	{-1, 0},
	 1, 0,
	 0,-1,
	 0, 1,
};

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%s", G[i] + 1);
		}
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) if (G[i][j] == '.') {
				int cnt = 0;
				for (int k = 0; k < 4; ++k) {
					int x = i + Move[k][0];
					int y = j + Move[k][1];
					if (x >= 1 && x <= n && y >= 1 && y <= n && G[x][y] == '.') {
						++cnt;
					}
				}
				if (cnt == 4) {
					G[i][j] = '#';
					for (int k = 0; k < 4; ++k) {
						int x = i + Move[k][0];
						int y = j + Move[k][1];
						G[x][y] = '#';
					}
				}
			}
		}
		bool flag = true;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				if (G[i][j] == '.') {
					flag = false;
					break;
				}
			}
		}
		puts(flag ? "YES" : "NO");
	}
	return 0;
}
