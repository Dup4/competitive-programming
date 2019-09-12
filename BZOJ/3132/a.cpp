#include <bits/stdc++.h>
using namespace std;

#define N 2050
int n, m, x[2], y[2], v;
struct BIT_2D {
	int a[N][N][4];
	void init() { memset(a, 0, sizeof a); }
	void update(int x, int y, int v) {
		for (int i = x; i <= n; i += i & -i)
			for (int j = y; j <= m; j += j & -j) {
				a[i][j][0] += v;
				a[i][j][1] += v * x;
				a[i][j][2] += v * y;
				a[i][j][3] += v * x * y;
			}
	}
	int query(int x, int y) {
		int res = 0;
		for (int i = x; i; i -= i & -i)
			for (int j = y; j; j -= j & -j) {
				res += a[i][j][0] * (x + 1) * (y + 1);
				res -= a[i][j][1] * (y + 1);
				res -= a[i][j][2] * (x + 1);
				res += a[i][j][3];

			}
		return res;
	}
	void update(int x[], int y[], int val) {
		int dx[4] = { x[0], x[1] + 1, x[0], x[1] + 1 };
		int dy[4] = { y[0], y[1] + 1, y[1] + 1, y[0] };
		int v[4] = { val, val, -val, -val };
		for (int i = 0; i < 4; ++i)
			update(dx[i], dy[i], v[i]);
	}
	int query(int x[], int y[]) {
		int dx[4] = { x[0] - 1, x[1], x[0] - 1, x[1] };
		int dy[4] = { y[0] - 1, y[1], y[1], y[0] - 1 };
		int v[4] = { 1, 1, -1, -1 };
		int res = 0;
		for (int i = 0; i < 4; ++i)
			res += v[i] * query(dx[i], dy[i]);
		return res;
	}
}bit;

int main() {
	char op[10]; 
	while (scanf("%s", op) != EOF) {
		if (op[0] == 'X') {
			scanf("%d%d", &n, &m);
			bit.init();
		}
		else {
			for (int i = 0; i < 2; ++i) scanf("%d%d", x + i, y + i);
			if (op[0] == 'L') {
				scanf("%d", &v);
				bit.update(x, y, v);
			}
			else printf("%d\n", bit.query(x, y));
		}
	}
	return 0;
}
