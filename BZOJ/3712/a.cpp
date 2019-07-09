#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 500010
int n, m, k, g[N];
struct Graph {
	struct node {
		int to, nx;
		node() {}
		node(int to, int nx) : to(to), nx(nx) {}
	}a[N << 1];
	int head[N], pos;
	void init() {
		memset(head, -1, sizeof head);
		pos = 0;
	}
	void add(int u, int v) {
		a[pos] = node(v, head[u]); head[u] = pos++;
	}
}G;
#define erp(u) for (int it = G.head[u], v = G.a[it].to; ~it; it = G.a[it].nx, v = G.a[it].to)

int f[N];
int find(int u) {
	return f[u] == u ? u : f[u] = find(f[u]); 
}

int fa[N], deep[N], sze[N], son[N], top[N]; 
void DFS(int u) {
	sze[u] = 1;
	erp(u) if (v != fa[u]) {
		fa[v] = u;
		deep[v] = deep[u] + 1;
		DFS(v);
		sze[u] += sze[v];
		if (!son[u] || sze[v] > sze[son[u]]) son[u] = v; 
	}
}
void gettop(int u, int tp) {
	top[u] = tp;
	if (!son[u]) return;  
	gettop(son[u], tp);
	erp(u) if (v != fa[u] && v != son[u]) {
		gettop(v, v);
	}
}

int query(int u, int v) {
	while (top[u] != top[v]) {
		if (deep[top[u]] < deep[top[v]]) swap(u, v);
		u = fa[top[u]];
	}
	if (deep[u] > deep[v]) swap(u, v);
	return u;    
}

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

void init() {
	for (int i = 1; i <= n; ++i) {
		f[i] = i;
	}
	G.init();
	memset(son, 0, sizeof son);
	memset(deep, 0, sizeof deep);
	memset(top, 0, sizeof top);
}
int main() { 
	while (scanf("%d%d%d", &n, &m, &k) != EOF) {
		init();
		for (int i = 1; i <= n; ++i) scanf("%d", g + i);
		for (int i = 1, u, v; i <= m; ++i) {
			scanf("%d%d", &u, &v);
			u = find(u); v = find(v);		
			G.add(n + i, u);
			G.add(n + i, v);
			f[u] = f[v] = n + i; 	
			f[n + i] = n + i;	 
		}
		for (int i = n + m; i >= 1; --i) if (top[i] == 0) {
			DFS(i); gettop(i, i);
		}
		int _q = 0;
		for (int i = 1, c, d; i <= k; ++i) {
			scanf("%d%d", &c, &d);
			if (find(c) != find(d)) continue;
			int lca = query(c, d); 
			Q[++_q] = qnode(deep[lca], i, c, d);
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
