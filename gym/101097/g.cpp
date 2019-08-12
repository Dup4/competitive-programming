#include <bits/stdc++.h>

using namespace std;

#define N 3010

int n, m;
int vis[N];
int G[N][N];

int main() {
	freopen("party.in", "r", stdin);
	freopen("party.out", "w", stdout);
	while (scanf("%d %d", &n, &m) != EOF) {
		memset(vis, 0, sizeof vis);
		memset(G, 0, sizeof G);
		for (int i = 1, u, v; i <= m; ++i) {
			scanf("%d %d", &u, &v);
			G[u][v] = G[v][u] = 1;
		}
		for (int i = 1; i <= n; ++i) {
			if (vis[i]) continue;
			for (int j = i + 1; j <= n; ++j) {
				if (!vis[j] && !G[i][j]) {
					vis[i] = vis[j] = 1;
					break;
				}
			}
		}
		vector<int> res;
		for (int i = 1; i <= n; ++i) {
			if (!vis[i]) {
				res.push_back(i);
			}
		}
		for (int i = 0; i < n / 3; ++i) {
			printf("%d%c", res[i], " \n"[i == n / 3 - 1]);
		}
	}
	return 0;
}
