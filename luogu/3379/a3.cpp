#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10;
int n, q, rt; 

struct Graph {
	struct E { int to, nx, w; }e[N << 1]; int h[N], cnt;
	void init(int n) { for (int i = 1; i <= n; ++i) h[i] = -1; cnt = -1; }
	void addedge(int u, int v, int w = 0) { e[++cnt] = { v, h[u], w}; h[u] = cnt; } 
}G;

struct UFS {
	int fa[N];
	void init(int n) { memset(fa, 0, sizeof (fa[0]) * (n + 5)); }
	int find(int x) { return fa[x] == 0 ? x : fa[x] = find(fa[x]); }
	bool merge(int x, int y) {
		int fx = find(x), fy = find(y);
		//有向合并
		if (fx != fy) {
			fa[fx] = fy;
			return true;
		}
		return false;
	}
}ufs;

struct LCA {
	int ans[N], used[N];
	struct E { int v, id; };
	vector <vector<E>> qvec;
	void init(int n) { 
		memset(used, 0, sizeof (used[0]) * (n + 5));
		qvec.clear();
		qvec.resize(n + 1);
		ufs.init(n);
	}
	void addquery(int u, int v, int id) { qvec[u].push_back({v, id}); qvec[v].push_back({u, id}); }
	void dfs(int u, int fa) {
		for (int i = G.h[u]; ~i; i = G.e[i].nx) {
			int v = G.e[i].to;
			if (v == fa) continue;
			dfs(v, u);
			ufs.merge(v, u);
			used[v] = 1;
		}
		for (auto &it : qvec[u]) {
			if (used[it.v]) {
				ans[it.id] = ufs.find(it.v);
			}
		}
	}
	void gao(int rt) {
		dfs(rt, rt);
		for (int i = 1; i <= q; ++i)
			printf("%d\n", ans[i]);
	}
}lca;

int main() {
	while (scanf("%d%d%d", &n, &q, &rt) != EOF) {
		G.init(n);
		for (int i = 1, u, v; i < n; ++i) {
			scanf("%d%d", &u, &v);
			G.addedge(u, v);
			G.addedge(v, u);
		}
		lca.init(n);
		for (int i = 1, u, v; i <= q; ++i) {
			scanf("%d%d", &u, &v);
			lca.addquery(u, v, i);
		}
		lca.gao(rt);
	}
	return 0;
}
