#include <bits/stdc++.h>
using namespace std;
const int N = 1e2 + 10;
int n, ans[N], g[N][N], res;

bool ok(int x, int y) {
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (!(x == i && y == j)) {
				if (g[i][j] == 1) {
					if (i == x)
						return false;
					if (j == y) 
						return false;
					if (i + j == x + y)
						return false;
					if (i - j == x - y)
						return false;					
				}
			}
		}
	}
	return true;
}

void dfs(int cur) {
	if (cur == n + 1) {
		++res;
		return;
	}
	for (int i = 1; i <= n; ++i) {
		if (ok(cur, i)) {
			g[cur][i] = 1;
			dfs(cur + 1);
			g[cur][i] = 0;
		}
	}
}

int main() {
	memset(ans, -1, sizeof ans);
    while (scanf("%d", &n), n) {
		if (ans[n] != -1) {
			printf("%d\n", ans[n]);
			continue;
		}
		memset(g, 0, sizeof g);
		res = 0;
		dfs(1);	
		ans[n] = res;
		printf("%d\n", ans[n]);
	}
	return 0;
}
