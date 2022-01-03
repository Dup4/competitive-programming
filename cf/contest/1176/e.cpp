#include <bits/stdc++.h>
using namespace std;

#define N 200010
int n, m;
vector < vector <int> > G;
int vis[N], deep[N], cnt[N], Max; 
void DFS(int u) {
	Max = max(Max, deep[u]);
	++cnt[deep[u]];
	for (auto v : G[u]) if (!vis[v]) {
		deep[v] = deep[u] + 1;
		DFS(v);
	}
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		G.clear();
		G.resize(n + 1);
		Max = 0;
		for (int i = 1; i <= n; ++i) {
			vis[i] = 0;
			cnt[i] = 0;
		}
		for (int i = 1, u, v; i <= m; ++i) {
			scanf("%d%d", &u, &v);
			G[u].push_back(v);
			G[v].push_back(u); 
		}
		deep[1] = 1;
		DFS(1);
		
		
		
	}
	return 0;
}
