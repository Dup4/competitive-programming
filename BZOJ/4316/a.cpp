#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
//f[i][0/1][0/1]　表示第i个点选不选，其所在环的底端的点选不选的最大权值
int n, m, fa[N], deep[N], c[N], isbottom[N], f[N][2][2];
vector <vector<int>> G;
void dfs(int u) {
	for (auto &v : G[u]) if (v != fa[u]) {
		//对每个点进行染色，标记其所在环
		if (deep[v] && deep[v] < deep[u]) {
			++*c;
			int it = u;
			while (1) {
				c[it] = *c;
				if (it == v) break;
				it = fa[it];
			}		
		} else {
			fa[v] = u;
			deep[v] = deep[u] + 1;
			dfs(v);
		}
	}
}

void dp(int u) {
	memset(f[u], 0, sizeof f[u]);
	//环的顶端
	if (u == 1 || c[u] != c[fa[u]]) {
		f[u][1][0] = 1;
	}	
	
}


int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		G.clear(); G.resize(n + 1);
		for (int i = 1, u, v; i <= m; ++i) {
			scanf("%d%d", &u, &v);
			G[u].push_back(v);
			G[v].push_back(u);
		}
		memset(c, 0, sizeof c);
		memset(deep, 0, sizeof deep);
		fa[1] = 0; deep[1] = 1;
		dfs(1);
	}
	return 0;
}
