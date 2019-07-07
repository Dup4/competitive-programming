#include <bits/stdc++.h>
using namespace std;

#define N 100010
#define pii pair <int, int>
#define fi first
#define se second
int n, q; 
struct node {
	int u, v, w, id;
	node() {}
	node(int v, int w) : v(v), w(w) {}
	node (int u, int v, int w, int id = 0) : u(u), v(v), w(w), id(id) {}
};
vector <vector<node>> E, Q, G;  
int res[N];  

int fa[N], deep[N], dis[N], sze[N], son[N], top[N], in[N], cnt;
void DFS(int u) {
	sze[u] = 1;
	for (auto it : G[u]) if (it.v != fa[u]) {
		int v = it.v;
		fa[v] = u;
		deep[v] = deep[u] + 1;
		dis[v] = dis[u] + it.w;
		DFS(v);
		sze[u] += sze[v];
		if (son[u] == -1 || sze[v] > sze[son[u]]) son[u] = v;
	}
}
void gettop(int u, int sp) {
	top[u] = sp;
	in[u] = ++cnt;
	if (son[u] == -1) return;
	gettop(son[u], sp);
	for (auto it : G[u]) {
		int v = it.v;
		if (v == fa[u] || v == son[u]) continue;
		gettop(v, v);
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

pii add(pii x, pii y) {
	return pii(x.fi + y.fi, x.se + y.se);
}
pii sub(pii x, pii y) {
	return pii(x.fi - y.fi, x.se - y.se);
}
struct BIT {
	pii a[N];
	void init() {
		memset(a, 0, sizeof a);
	}
	void update(int x, int s, int t) {
		for (; x < N; x += x & -x) {
			a[x] = add(a[x], pii(s, t));
		}
	}
	pii query(int x) {
		pii res = pii(0, 0);
		for (; x > 0; x -= x & -x) {
			res = add(res, a[x]);
		}
		return res;
	}
	pii query(int l, int r) {
		return sub(query(r), query(l - 1));
	}
}bit;

pii query(int u, int v) {
	pii res = pii(0, 0);
	while (top[u] != top[v]) {
		if (deep[top[u]] < deep[top[v]]) swap(u, v);
		res = add(res, bit.query(in[top[u]], in[u]));
		u = fa[top[u]];	
	}
	if (u == v) return res;
	if (deep[u] > deep[v]) swap(u, v);
	return add(res, bit.query(in[son[u]], in[v]));
}

void init() {
	bit.init();
	cnt = 0; dis[1] = 0; fa[1] = 0;
	E.clear(); E.resize(n + 1);
	Q.clear(); Q.resize(n + 1);
	G.clear(); G.resize(n + 1);
	memset(son, -1, sizeof son);
	memset(res, 0, sizeof res);
}
int main() {
	while (scanf("%d%d", &n, &q) != EOF) {
		init();
		for (int i = 1, u, v, c, d; i < n; ++i) {
			scanf("%d%d%d%d", &u, &v, &c, &d);
			G[u].push_back(node(v, d));
			G[v].push_back(node(u, d));
			E[c].push_back(node(u, v, d));
		}
		for (int i = 1, c, u, v, w; i <= q; ++i) {
			scanf("%d%d%d%d", &c, &w, &u, &v);
			Q[c].push_back(node(u, v, w, i));
		}
		DFS(1); gettop(1, 1);
	//	for (int i = 1; i <= n; ++i) printf("%d %d %d %d\n", i, fa[i], son[i], in[i]);
		for (int i = 1; i < n; ++i) {
			if (Q[i].empty()) continue;
			for (auto &it : E[i]) {
				if (fa[it.u] == it.v) swap(it.u, it.v);
				bit.update(in[it.v], 1, it.w);
			}
			for (auto it : Q[i]) {
				int u = it.u, v = it.v, w = it.w, id = it.id;
				int lca = querylca(u, v); 
			//	cout << u << " " << v << " " << lca << endl;
				pii tmp = query(u, v);
				res[id] = dis[u] + dis[v] - 2 * dis[lca] - tmp.se + w * tmp.fi;
			}
			for (auto it : E[i]) {
				bit.update(in[it.v], -1, -it.w);
			}
		}
		for (int i = 1; i <= q; ++i) printf("%d\n", res[i]);
	}
	return 0;
}
