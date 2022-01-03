#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair <int, int>
#define pll pair <ll, ll>
#define fi first
#define se second
const int N = 5e5 + 10;
struct qnode {
	int tp, u, v, k;
	qnode() {}
	qnode(int tp, int u, int v, int k) : tp(tp), u(u), v(v), k(k) {}
}qrr[2010];
struct Edge {
	int v, cnt; ll w;
	Edge() {}
	Edge(int v, int cnt, ll w) : v(v), cnt(cnt), w(w) {}
}e[N]; 
vector <vector<int>> G1; 
vector <vector<Edge>> G2;
int n, m, k, a[10010], Sta[10010], fa[N], deep[N], sze[N], son[N], top[N], in[N], out[N], cnt;
ll w[N]; 
void predfs(int u) { 
	sze[u] = 1; son[u] = 0;
	for (auto v : G1[u]) {
		if (v == fa[u]) continue; 
		fa[v] = u;
		deep[v] = deep[u] + 1;
		predfs(v);
		sze[u] += sze[v];
		if (!son[u] || sze[v] > sze[son[u]]) son[u] = v;
	}
}
void gettop(int u, int tp) {
	top[u] = tp;
	in[u] = ++cnt;
	if (son[u]) gettop(son[u], tp);
	for (auto v : G1[u]) {
	    if (v == fa[u] || v == son[u]) continue;
   		gettop(v, v);   
	}
	out[u] = cnt;
}
void predfs2(int u) {
	sze[u] = 1; son[u] = 0; 
	for (auto it : G2[u]) {
		int v = it.v;
		if (v == fa[u]) continue;
		e[v] = it; 
		fa[v] = u; deep[v] = deep[u] + 1;
		predfs2(v);
		sze[u] += sze[v];
		if (!son[u] || sze[v] > sze[son[u]]) son[u] = v;
	}
}
void gettop2(int u, int tp) {
	top[u] = tp;
	in[u] = ++cnt;
	if (son[u]) gettop2(son[u], tp); 
	for (auto it : G2[u]) {
		int v = it.v;
		if (v == fa[u] || v == son[u]) continue;
		gettop2(v, v);
	}
	out[u] = cnt;
}
inline int querylca(int u, int v) {
	while (top[u] != top[v]) {
		if (deep[top[u]] < deep[top[v]]) swap(u, v);
		u = fa[top[u]];
	}
	if (deep[u] > deep[v]) swap(u, v);
	return u;
}
inline int dis(int u, int v) {
	return deep[u] + deep[v] - 2 * deep[querylca(u, v)];  
}
inline void gao1(int u, int lca, int k) {
	while (u != lca) {
		w[u] += k;
		if (e[u].cnt) e[u].w += k;
		u = fa[u];
	}
}
inline void gao2(int u, int lca, int k) {
	while (u != lca) {
		w[u] ^= k;
		if (e[u].cnt) e[u].w ^= k;
		u = fa[u];
	}
}
inline void gao3(int u, int lca, int k) {
	while (u != lca) {
		if (w[u] >= k) w[u] -= k;
		if (e[u].cnt && e[u].w >= k) e[u].w -= k;
		u = fa[u];
	}
}
inline ll gao4(int u, int lca) {
	ll res = 0;
	while (u != lca) {
		res += w[u];
		res += e[u].w * e[u].cnt;
		u = fa[u];
	}
	return res;
}
inline ll gao5(int u, int lca) {
	ll res = 0;
	while (u != lca) {
		res ^= w[u];
		if (e[u].cnt & 1) res ^= e[u].w;
		u = fa[u];
	}
	return res;
}
inline pll gao6(int u, int lca) {
	pll res = pll(0, 1e18);
	while (u != lca) {
		res.fi = max(res.fi, w[u]);
		res.se = min(res.se, w[u]);
		if (e[u].cnt) {
			res.fi = max(res.fi, e[u].w);
			res.se = min(res.se, e[u].w);
		}
		u = fa[u];
	}
	return res;
}
inline ll gao7(int u, int lca, int k) {
	ll res = 1e18;
	while (u != lca) {
		res = min(res, abs(w[u] - k));
		if (e[u].cnt) res = min(res, abs(e[u].w - k));
		u = fa[u];
	}
	return res;
}

int main() {
	int _T; scanf("%d", &_T);
	while (_T--) {
		scanf("%d%d", &n, &m);
		G1.clear(); G1.resize(n + 1);
		for (int i = 1, u, v; i < n; ++i) {
			scanf("%d%d", &u, &v);
			G1[u].push_back(v);
			G1[v].push_back(u);
		}
		cnt = 0; fa[1] = 1; deep[1] = 0;
		predfs(1); gettop(1, 1);
		a[0] = 0;
		for (int i = 1, tp, u, v, k; i <= m; ++i) {
			scanf("%d%d%d", &tp, &u, &v);
			if (tp < 4 || tp > 6) scanf("%d", &k);
			qrr[i] = qnode(tp, u, v, k); 
			a[++a[0]] = u;
			a[++a[0]] = v;
		}
		a[++a[0]] = 1; 
		sort(a + 1, a + 1 + a[0], [&](int x, int y) {
			return in[x] < in[y];		
		});
		a[0] = unique(a + 1, a + 1 + a[0]) - a - 1;
		k = a[0];
		for (int i = k; i > 1; --i) {
			a[++a[0]] = querylca(a[i], a[i - 1]);
		}	
		sort(a + 1, a + 1 + a[0], [&](int x, int y){
			return in[x] < in[y];		
		});
		a[0] = unique(a + 1, a + 1 + a[0]) - a - 1;
		G2.clear(); G2.resize(n + 1); 
		for (int i = 1, top = 0; i <= a[0]; ++i) {
			while (top && out[Sta[top]] < in[a[i]]) {
				--top;
			}
			if (top) {
				int u = Sta[top], v = a[i], cnt = dis(u, v) - 1;
				G2[u].push_back(Edge(v, cnt, 0));
				G2[v].push_back(Edge(u, cnt, 0));
			}
			Sta[++top] = a[i];   
		} 
		cnt = 0; fa[1] = 1; deep[1] = 0;
		predfs2(1); gettop2(1, 1);
		memset(w, 0, sizeof w);
		for (int i = 1; i <= m; ++i) {
			int tp = qrr[i].tp, u = qrr[i].u, v = qrr[i].v, k = qrr[i].k, lca = querylca(u, v);
			if (tp == 1) {
				gao1(u, lca, k); 
				gao1(v, lca, k);
				w[lca] += k;
			} else if (tp == 2) {
				gao2(u, lca, k);
				gao2(v, lca, k);
				w[lca] ^= k;	
			} else if (tp == 3) {
				gao3(u, lca, k);
				gao3(v, lca, k);
				if (w[lca] >= k) w[lca] -= k;
			} else if (tp == 4) {
				ll res = 0;
				res += gao4(u, lca);
				res += gao4(v, lca); 
				res += w[lca];
				printf("%lld\n", res);
			} else if (tp == 5) {
				ll res = 0;
				res ^= gao5(u, lca);
				res ^= gao5(v, lca);
				res ^= w[lca];
				printf("%lld\n", res);
			} else if (tp == 6) {
				pll tu = gao6(u, lca);
				pll tv = gao6(v, lca);
				tu.fi = max(tu.fi, max(tv.fi, w[lca]));
				tu.se = min(tu.se, min(tv.se, w[lca]));
				ll res = tu.fi - tu.se; 
				printf("%lld\n", res);
			} else if (tp == 7) {
				ll res = 1e18;
				res = min(res, gao7(u, lca, k));
				res = min(res, gao7(v, lca, k));
				res = min(res, abs(w[lca] - k));
				printf("%lld\n", res);
			}
		}
	}
	return 0;
}
