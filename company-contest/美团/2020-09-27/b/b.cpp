#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int n, m, q, f[N], g[N];

int main() {
	scanf("%d%d%d", &n, &m, &q);
	memset(f, 0, sizeof f);
	memset(g, 0, sizeof g);
	for (int i = 1, op, x, y; i <= q; ++i) {
		scanf("%d", &op);
		if (op == 1) scanf("%d%d", &x, &y);
		else if (op < 4) scanf("%d", &y);
		else scanf("%d", &x);
		if (op == 1) {
			if (f[x] == -1 || g[y] == 1 || g[f[x]] == 1) continue;
			f[x] = y;
		} else if (op == 2) {
			g[y] = 1;
		} else if (op == 3) {
			g[y] = 0;
		} else if (op == 4) {
			int res = -1;
			if (f[x] > 0 && g[f[x]] == 0) {
				res = f[x];
				f[x] = -1;
			}
			printf("%d\n", res);
		} else {
			if (f[x] == -1) f[x] = 0;
		}
	}
	return 0;
}
