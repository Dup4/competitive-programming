#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 5e5 + 10;
int n, m, k, g[N], e[N][2];
struct Graph {
	struct E { int to, nx; }e[N << 1]; int h[N], cnt;
	void init(int n) { for (int i = 1; i <= n; ++i) h[i] = -1; cnt = -1; }
	void addedge(int u, int v) { e[++cnt] = { v, h[u]}; h[u] = cnt; } 
}G;

struct UFS {
	int fa[N];
	void init(int n) { memset(fa, 0, sizeof (fa[0]) * (n + 5)); }
	int find(int x) { return fa[x] == 0 ? x : fa[x] = find(fa[x]); }
	void build(int n, int m) {
		G.init(n + m); init(n + m);
		for (int i = 1; i <= m; ++i) {
			int u = e[i][0], v = e[i][1];
			int fu = find(u), fv = find(v);
			if (fu == fv) continue;
			G.addedge(n + i, fu); fa[fu] = n + i;
			G.addedge(n + i, fv); fa[fv] = n + i;
		}
	}
}ufs;

struct LCA {
	int fa[N], deep[N], sze[N], son[N], top[N]; 
	void dfs(int u) {
		sze[u] = 1; son[u] = 0;
		for (int i = G.h[u]; ~i; i = G.e[i].nx) {
			int v = G.e[i].to;
			if (v == fa[u]) continue;
			fa[v] = u; deep[v] = deep[u] + 1; 
			dfs(v);
			sze[u] += sze[v];
			if (!son[u] || sze[v] > sze[son[u]]) son[u] = v; 
		}
	}
	void gettop(int u, int tp) {
		top[u] = tp;
		if (son[u]) gettop(son[u], tp);
		for (int i = G.h[u]; ~i; i = G.e[i].nx) {
			int v = G.e[i].to;
			if (v != son[u] && v != fa[u]) {
				gettop(v, v);
			}
		}
	}
	void init(int n) {
		for (int i = 1; i <= n; ++i) {
			if (ufs.fa[i] == 0) {
				fa[i] = i;
				dfs(i);
				gettop(i, i);
			}
		}
	} 
	int querylca(int u, int v) {
		while (top[u] != top[v]) {
			if (deep[top[u]] < deep[top[v]]) {
				swap(u, v);
			}
			u = fa[top[u]];
		}
		if (deep[u] > deep[v]) swap(u, v);
		return u;
	}
}lca;

struct qnode {
	int dep, id, c, d;
	qnode() {}
	qnode(int dep, int id, int c, int d) : dep(dep), id(id), c(c), d(d) {}
	bool operator < (const qnode &other) const {
		if (dep != other.dep) {
			return dep > other.dep;
		}
		return id < other.id;
	}
}Q[N];

int main() { 
	while (scanf("%d%d%d", &n, &m, &k) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%d", g + i);
		for (int i = 1; i <= m; ++i) {
			scanf("%d%d", e[i], e[i] + 1);
		}
		ufs.build(n, m);
		lca.init(n + m);
		int _q = 0;
		for (int i = 1, c, d; i <= k; ++i) {
			scanf("%d%d", &c, &d);
			if (ufs.find(c) != ufs.find(d)) continue;
			Q[++_q] = qnode(lca.deep[lca.querylca(c, d)], i, c, d);
		}
		ll ans = 0;
		sort(Q + 1, Q + 1 + _q);
		for (int i = 1, c, d; i <= _q; ++i) {
			c = Q[i].c, d = Q[i].d;
			ll get = min(g[c], g[d]);
			ans += get;
			g[c] -= get;
			g[d] -= get;
		}
		printf("%lld\n", ans + ans);
	}
	return 0;
}
