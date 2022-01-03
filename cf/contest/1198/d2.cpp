#include <bits/stdc++.h>
using namespace std;
#define debug(...) { printf("#  "); printf(__VA_ARGS__); puts(""); }
const int N = 50 + 10;
int n;
char s[N][N];
int f[N][N][N][N];

void Min(int &x, int y) {
	if (x > y) x = y;
} 

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%s", s[i] + 1);
		memset(f, 0x3f, sizeof f);
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				f[i][i][j][j] = (s[i][j] == '#' ? 1 : 0);
			}
		}
		for (int dx = 1; dx <= n; ++dx) {
			for (int dy = 1; dy <= n; ++dy) {
				for (int x = 1; x + dx - 1 <= n; ++x) {
					for (int y = 1; y + dy - 1 <= n; ++y) {
						int w = max(dx, dy);
						int ex = x + dx - 1, ey = y + dy - 1;
						Min(f[x][ex][y][ey], w);
						for (int i = x; i < ex; ++i) {
							Min(f[x][ex][y][ey], f[x][i][y][ey] + f[i + 1][ex][y][ey]);
						}
						for (int i = y; i < ey; ++i) {
							Min(f[x][ex][y][ey], f[x][ex][y][i] + f[x][ex][i + 1][ey]);
						}
					}
				}
			}
		}
		printf("%d\n", f[1][n][1][n]);
	}
	return 0;
}
