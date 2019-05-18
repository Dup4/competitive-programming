#include <bits/stdc++.h>
using namespace std;

#define N 10010
struct node {
	int a, x, y;
	node () {}
	node (int a, int x, int y) : a(a), x(x), y(y) {}
	bool operator < (const node &other) const {
		return a < other.a;
	}
}a[N], g[N][3];
int n, m, T, q, G[N][N];
int f[N];
bool ok(int ax, int ay, int bx, int by) {
	if (ax == -1 || ay == -1) {
		return true;
	}
	if ((ax + 1 == bx && ay == by) ||
		(ax == bx && ay + 1 == by)) {
		return true;
	}
	return false;
}

int main() {
	while (scanf("%d%d%d", &n, &m, &T) != EOF) {
		q = 0;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				scanf("%d", &G[i][j]);
				a[++q] = node(G[i][j], i, j);		
			}
		}
		sort(a + 1, a + 1 + q);
		memset(f, 0, sizeof f);
		memset(g, 0, sizeof g);
		for (int i = 0; i <= q; ++i) {
			for (int j = 0; j < 3; ++j) {
				g[i][j] = node(0, -1, -1); 
			}
		}
		for (int i = 1; i <= q; ++i) {
			for (int j = 0; j <= q; ++j) {
				int x = a[i].x, y = a[i].y;
				for (int k = 0; k < 3; ++k) {
					int prex = g[j][k].x, prey = g[j][k].y, a = g[j][k].a;
					if (ok(prex, prey, x, y)) {
						f[j] = max(f[j], a + 1); 
					} else {
						f[j + 1] = max(f[j + 1], a + 1);   
					}
				}
				int t = f[j], nx = x, ny = y;
				for (int k = 0; k < 3; ++k) {
					int a = g[j][k].a;
					nx = g[j][k].x, ny = g[j][k].y;
					if (t > a) {
						g[j][k] = node(t, x, y);
						x = nx, y = ny; t = a;
					}
				}
			}
		}
		int res = 0;
		for (int i = 0; i <= min(q, T); ++i) {
			res = max(res, f[i] - i);
		}
		printf("%d\n", res + T);
		
	
	}
	return 0;
}
