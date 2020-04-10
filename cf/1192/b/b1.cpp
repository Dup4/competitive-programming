#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
const ll INF = 1e18;
int n, q; ll W;
struct Edge { int u, v; ll w; }e[N]; 

struct Graph {
	struct E { int to, nx; ll w; }e[N << 1]; int h[N], cnt;
	void init(int n) { for (int i = 0; i <= n; ++i) h[i] = -1; cnt = -1; }
	void addedge(int u, int v, ll w = 0) { e[++cnt] = { v, h[u], w}; h[u] = cnt; } 
}G;

struct SEG {
	struct node {
		ll val, lazy;
		node() { val = lazy = 0; }
		void up(ll _lazy) {
			lazy += _lazy;
			val += _lazy;
		}
		node operator + (const node &other) const {
			node res = node();
			res.val = max(val, other.val);
			return res;
		}
	}t[N << 2];
	void build(int id, int l, int r) {
		t[id] = node();
		if (l == r) return;
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
	}
	void pushdown(int id) {
		ll &lazy = t[id].lazy;
		t[id << 1].up(lazy);
		t[id << 1 | 1].up(lazy);
		lazy = 0;
	}
	void update(int id, int l, int r, int ql, int qr, ll v) {
		if (ql > qr) return;
		if (l >= ql && r <= qr) {
			t[id].up(v);
			return;
		}
		int mid = (l + r) >> 1;
		pushdown(id);
		if (ql <= mid) update(id << 1, l, mid, ql, qr, v);
		if (qr > mid) update(id << 1 | 1, mid + 1, r, ql, qr, v);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	ll query(int id, int l, int r, int ql, int qr) {
		if (ql > qr) return -INF;
		if (l >= ql && r <= qr) return t[id].val;
		int mid = (l + r) >> 1;
		pushdown(id);
		ll res = -INF;
		if (ql <= mid) res = max(res, query(id << 1, l, mid, ql, qr));
		if (qr > mid) res = max(res, query(id << 1 | 1, mid + 1, r, ql, qr));
		return res;
	}
	int getPos(int id, int l, int r, ll v) {
		if (l == r) return l;
		int mid = (l + r) >> 1;
		pushdown(id);
		if (t[id << 1].val == v) return getPos(id << 1, l, mid, v);
		else return getPos(id << 1 | 1, mid + 1, r, v);
	}
	void modify(int pos, ll v) {
		ll pre = query(1, 1, n, pos, pos);
	   	update(1, 1, n, pos, pos, v - pre);	
	}
}seg[2];

struct HLD { 
	int fa[N], deep[N], sze[N], son[N], top[N], in[N], fin[N], out[N]; 
	ll dis[N], weight[N]; 
	void dfs(int u) {
		sze[u] = 1; son[u] = 0;
		for (int i = G.h[u]; ~i; i = G.e[i].nx) {
			int v = G.e[i].to; ll w = G.e[i].w;
			if (v == fa[u]) continue;
			fa[v] = u; 
			deep[v] = deep[u] + 1; 
			weight[v] = w;
			dis[v] = dis[u] + w;
			dfs(v);
			sze[u] += sze[v];
			if (!son[u] || sze[v] > sze[son[u]]) son[u] = v; 
		}
	}
	void gettop(int u, int tp) { 
		in[u] = ++*in;
		fin[*in] = u;
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
	void modify(int u, ll w) {
		seg[0].update(1, 1, n, in[u], out[u], w - weight[u]);
		seg[1].update(1, 1, n, in[u], out[u], weight[u] - w);
		weight[u] = w;
		while (u) {
			u = fa[top[u]]; 
			if (u) {
				ll Max = max(seg[0].query(1, 1, n, in[u], in[u]), seg[0].query(1, 1, n, out[son[u]] + 1, out[u]));
				seg[1].modify(in[u], Max - seg[0].query(1, 1, n, in[u], in[u]) * 2);
			}		
		}	
	}
	ll diameter() {
		ll Mdis = seg[0].t[1].val;
		int u = fin[seg[0].getPos(1, 1, n, Mdis)];
		ll res = 0;
		while (u) {
			int _u = top[u];
			if (in[_u] < in[u]) {
				res = max(res, seg[1].query(1, 1, n, in[_u], in[u] - 1));
			}
			u = fa[_u];
			if (u) {
				ll Max = max(seg[0].query(1, 1, n, in[u], in[_u] - 1), seg[0].query(1, 1, n, out[_u] + 1, out[u]));
				res = max(res, Max - seg[0].query(1, 1, n, in[u], in[u]) * 2);
			}
		}
		return res + Mdis;
	}
	void gao() {
		*in = 0;
		fa[1] = 0; 
		deep[1] = 0;
		dfs(1);
		gettop(1, 1);
		for (int i = 1; i < n; ++i) {
			if (fa[e[i].u] == e[i].v)
				swap(e[i].u, e[i].v);
		}
		seg[0].build(1, 1, n);
		seg[1].build(1, 1, n);
		for (int i = 1; i <= n; ++i) {
			seg[0].update(1, 1, n, i, i, dis[fin[i]]); 
		}
		for (int i = 1; i <= n; ++i) {
			ll Max = dis[fin[i]];
			Max = max(Max, seg[0].query(1, 1, n, out[son[fin[i]]] + 1, out[fin[i]]));
			seg[1].update(1, 1, n, i, i, Max - dis[fin[i]] * 2);
		}
		ll lst = 0; 
		for (int i = 1; i <= q; ++i) {
			int _d; ll _w;
			scanf("%d%lld", &_d, &_w);
			_d = (_d + lst) % (n - 1) + 1;
			_w = (_w + lst) % W;
			modify(e[_d].v, _w);
			lst = diameter();
			printf("%lld\n", lst);
		}
	}
}hld;

int main() {
	while (scanf("%d%d%lld", &n, &q, &W) != EOF) {
		G.init(n);
		for (int i = 1; i < n; ++i) {
			scanf("%d%d%lld", &e[i].u, &e[i].v, &e[i].w);
			G.addedge(e[i].u, e[i].v, e[i].w);
			G.addedge(e[i].v, e[i].u, e[i].w);
		}
		hld.gao();
	}
	return 0;
}
