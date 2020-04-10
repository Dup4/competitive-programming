#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10, INF = 0x3f3f3f3f;
int n, q, rt, a[N]; 

struct BIT_2D {
    struct BIT {
        ll a[N];
		void init() { memset(a, 0, sizeof a); }
        void add(int x, ll v) { for (; x < N; a[x] += v, x += x & -x); }
        ll ask(int x) { ll res = 0; for (; x > 0; res += a[x], x -= x & -x); return res; }
    }bit1, bit2;
	void init() { bit1.init(); bit2.init(); }
    ll ask(int x) { return (x + 1) * bit1.ask(x) - bit2.ask(x); }
    void add(int x, ll v) { bit1.add(x, v); bit2.add(x, x * v); }
    ll ask(int l, int r) { return ask(r) - ask(l - 1); }
    void add(int l, int r, ll v) { add(l, v); add(r + 1, -v); }
}bit;

struct Graph {
	struct E { int to, nx, w; }e[N << 1]; int h[N], cnt;
	void init(int n) { for (int i = 0; i <= n; ++i) h[i] = -1; cnt = -1; }
	void addedge(int u, int v, int w = 0) { e[++cnt] = { v, h[u], w}; h[u] = cnt; } 
}G;

struct HLD {
	int fa[N], deep[N], dis[N], sze[N], son[N], top[N], in[N], fin[N], out[N]; 
	void dfs(int u) {
		sze[u] = 1; son[u] = 0;
		for (int i = G.h[u]; ~i; i = G.e[i].nx) {
			int v = G.e[i].to, w = G.e[i].w;
			if (v == fa[u]) continue;
			fa[v] = u; deep[v] = deep[u] + 1; dis[v] = dis[u] + w;
			dfs(v);
			sze[u] += sze[v];
			if (!son[u] || sze[v] > sze[son[u]]) son[u] = v; 
		}
	}
	void gettop(int u, int tp) {
		in[u] = ++*in; fin[*in] = u;
		top[u] = tp;
		if (son[u]) gettop(son[u], tp);
		for (int i = G.h[u]; ~i; i = G.e[i].nx) {
			int v = G.e[i].to;
			if (v != son[u] && v != fa[u]) {
				gettop(v, v);
			}
		}
		out[u] = *in;
	}
	void init(int rt) {
		fa[rt] = rt;
		dis[rt] = 0; 
		*in = 0;
		dfs(rt);
		gettop(rt, rt);
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
	int querydis(int u, int v) { return dis[u] + dis[v] - 2 * dis[querylca(u, v)]; }
	void updatePath(int u, int v, ll x) {
		while (top[u] != top[v]) {
			if (deep[top[u]] < deep[top[v]]) swap(u, v);
			bit.add(in[top[u]], in[u], x);
			u = fa[top[u]];	
		}
		if (deep[u] > deep[v]) swap(u, v);
		bit.add(in[u], in[v], x);
	}	
	ll queryPath(int u, int v) {
		ll res = 0;
		while (top[u] != top[v]) {
			if (deep[top[u]] < deep[top[v]]) swap(u, v);
			res += bit.ask(in[top[u]], in[u]);
			u = fa[top[u]];
		}
		if (deep[u] > deep[v]) swap(u, v);
		res += bit.ask(in[u], in[v]);
		return res;
	}
	bool inSubTree(int u, int v) { return in[v] >= in[u] && in[v] <= out[u]; }
	//找u在rt的哪个儿子的子树中
	int finds(int u, int rt) {
		while (top[u] != top[rt]) {
			u = top[u];
			if (fa[u] == rt) return u;
			u = fa[u];
		}
		return fin[in[rt] + 1];
	}
	//找u的k级祖先	
	int up(int u, int k) {
		while (k) {
			if (deep[u] - deep[top[u]] < k) {
				k -= deep[u] - deep[top[u]];
				u = top[u];
			} else {
				return fin[in[u] - k]; 
			}
			u = fa[u];
			--k;
		}
		return u;
	}
	void updateSubTree(int u, int rt, ll x) {
		if (u == rt) {
			bit.add(1, n, x);
		} else if (!inSubTree(u, rt)) {
			bit.add(in[u], out[u], x);
		} else {
			bit.add(1, n, x);
			int anc = finds(rt, u);
			bit.add(in[anc], out[anc], -x); 
		}
	}
	ll querySubTree(int u, int rt) {
		if (u == rt) {
			return bit.ask(1, n);
		} else if (!inSubTree(u, rt)) {
			return bit.ask(in[u], out[u]);
		} else {
			int anc = finds(rt, u);	
			return bit.ask(1, n) - bit.ask(in[anc], out[anc]);
		}
	}
}hld;

int main() {
	while (scanf("%d", &n) != EOF) {
		G.init(n); rt = 1; bit.init();
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		for (int i = 2, fa; i <= n; ++i) {
			scanf("%d", &fa);
			G.addedge(fa, i);
			G.addedge(i, fa);
		}
		hld.init(rt);
		for (int i = 1; i <= n; ++i) {
			hld.updatePath(i, i, a[i]);
		}
		scanf("%d", &q);
		for (int i = 1, op, u, v, k; i <= q; ++i) {
			scanf("%d", &op);
			if (op == 1) scanf("%d", &rt);
			else if (op == 2) {
				scanf("%d%d%d", &u, &v, &k);
				hld.updatePath(u, v, k);
			} else if (op == 3) {
				scanf("%d%d", &u, &k);
				hld.updateSubTree(u, rt, k);
			} else if (op == 4) {
				scanf("%d%d", &u, &v);
				printf("%lld\n", hld.queryPath(u, v));
			} else {
				scanf("%d", &u);
				printf("%lld\n", hld.querySubTree(u, rt));
			}
		}
	}
	return 0;
}
