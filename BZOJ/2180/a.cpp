#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 10, INF = 0x3f3f3f3f;
int n, m, ans, dis[N][N], rk[N][N];

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		memset(dis, 0x3f, sizeof dis);
		for (int i = 1; i <= n; ++i) dis[i][i] = 0;
		for (int i = 1, u, v, w; i <= m; ++i) {
			scanf("%d%d%d", &u, &v, &w);
			dis[u][v] = dis[v][u] = min(dis[u][v], w);
		}
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				rk[i][j] = j;
			}
		}
		for (int k = 1; k <= n; ++k) {
			for (int i = 1; i <= n; ++i) if (k != i) {
				for (int j = 1; j <= n; ++j) if (i != j && k != j) {
					dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
				}
			}
		}
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				for (int k = j + 1; k <= n; ++k) {
					if (dis[i][rk[i][j]] < dis[i][rk[i][k]]) {
						swap(rk[i][j], rk[i][k]);
					}
				}
			}
		}
		int ans = INF;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) if (i != j) {
				ans = min(ans, dis[i][rk[i][1]] + dis[i][rk[i][2]]);
				ans = min(ans, dis[j][rk[j][1]] + dis[j][rk[j][2]]);
				for (int b = 1, a = 2; a <= n; ++a) {
					if (dis[j][rk[i][b]] < dis[j][rk[i][a]]) {
						ans = min(ans, dis[j][rk[i][b]] + dis[i][rk[i][a]] + dis[i][j]), b = a;
					}
				}
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
