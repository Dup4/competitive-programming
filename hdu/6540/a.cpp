#include <bits/stdc++.h>
using namespace std;

#define N 5010
int n, m, k;
vector < vector <int> > G;
int vis[N], f[N][N];

void DFS(int u, int fa) {
	for (int i = 0; i <= k; ++i) {
		fa[u][i] = 0;
	}
	if (vis[u]) {
		f[u][0] = 1;
	}
	for (auto v : G[u]) if (v != fa) {
		DFS(v, u);
		
	}
}

void init() {
	G.clear();
	G.resize(n + 1);
	memset(vis, 0, sizeof vis);
}
int main() {
	while (scanf("%d%d%d", &n, &m, &k) != EOF) {
		init();
		for (int i = 1, u, v; i < n; ++i) {
			scanf("%d%d", &u, &v);
			G[u].push_back(v);
			G[v].push_back(u);
		}
		for (int i = 1, x; i <= m; ++i) {
			scanf("%d", &x);
			vis[x] = 1;
		}
		
	}
	return 0;
}
