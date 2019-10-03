#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int N = 2e5 + 10;
int n;
vector <vector<int>> G;
ll tmpf[N * 10], tmpg[N * 10], *f[N], *g[N], *tmp_f = tmpf, *tmp_g = tmpg, h[N], res;   
int fa[N], hson[N], md[N];
void dfs(int u) {
	md[u] = 1; 
	hson[u] = 0;
	for (auto &v : G[u]) if (v != fa[u]) {
		fa[v] = u;
		dfs(v);
		md[u] = max(md[u], md[v] + 1);
		if (!hson[u] || md[v] > md[hson[u]]) hson[u] = v;
	}
}

void dfs2(int u) {
	if (hson[u]) {
		int v = hson[u];
		f[v] = f[u] + 1;
		g[v] = g[u] - 1;
		dfs2(v);
	}
	++f[u][0];
	int Max = 0;
	for (auto &v : G[u]) if (v != fa[u] && v != hson[u]) {
		f[v] = tmp_f; tmp_f += md[v] * 2;
		g[v] = tmp_g; tmp_g += md[v] * 2;
		dfs2(v);
		Max = max(Max, md[v]);
		for (int i = 0; i <= md[v]; ++i) { 
			if (i) g[u][i] += f[u][i] * f[v][i - 1]; 
			if (i) res += h[i] * f[v][i - 1]; 
			if (i) h[i] += f[u][i] * f[v][i - 1];
			if (i) f[u][i] += f[v][i - 1];
			g[u][i] += g[v][i + 1];
		}
	}
	for (int i = 0; i <= Max; ++i) h[i] = 0;
	res += g[u][0];
}

int main() {
	int _T; cin >> _T;
	while (_T--) {
		scanf("%d", &n);
		G.clear(); G.resize(n + 1);
		memset(tmpf, 0, sizeof tmpf);
		memset(tmpg, 0, sizeof tmpg);
		memset(h, 0, sizeof h);
		res = 0;
		for (int i = 1, u, v; i < n; ++i) {
			scanf("%d%d", &u, &v);
			G[u].push_back(v);
			G[v].push_back(u);
		}
		dfs(1);
		f[1] = tmp_f, g[1] = tmp_g; tmp_f += md[1] * 2; tmp_g += md[1] * 2;
		dfs2(1);
		printf("%lld\n", res);
	}
	return 0;
}
