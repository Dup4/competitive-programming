#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10, INF = 0x3f3f3f3f;
int n, q, e[N][3];  

struct SEG {
	struct node {
		int Max;
		node() { Max = -INF; }
		node operator + (const node &other) const {
			node res = node();
			res.Max = max(Max, other.Max);
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
	void update(int id, int l, int r, int pos, int v) {
		if (l == r) {
			t[id].Max = v;
			return;
		}
		int mid = (l + r) >> 1;
		if (pos <= mid) update(id << 1, l, mid, pos, v);
		if (pos > mid) update(id << 1 | 1, mid + 1, r, pos, v);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	int query(int id, int l, int r, int ql, int qr) { 
		if (l >= ql && r <= qr) { return t[id].Max; }
		int mid = (l + r) >> 1;
		int Max = -INF;
		if (ql <= mid) Max = max(Max, query(id << 1, l, mid, ql, qr));
		if (qr > mid) Max = max(Max, query(id << 1 | 1, mid + 1, r, ql, qr));
		return Max;
	}
}seg;

struct Graph {
	struct E { int to, nx, w; }e[N << 1]; int h[N], cnt;
	void init(int n) { for (int i = 0; i <= n; ++i) h[i] = -1; cnt = -1; }
	void addedge(int u, int v, int w = 0) { e[++cnt] = { v, h[u], w}; h[u] = cnt; } 
}G;

struct HLD {
	int fa[N], deep[N], dis[N], sze[N], son[N], top[N], in[N], out[N];
	int val[N];
	void dfs(int u) {
		sze[u] = 1; son[u] = 0;
		for (int i = G.h[u]; ~i; i = G.e[i].nx) {
			int v = G.e[i].to, w = G.e[i].w;
			if (v == fa[u]) continue;
			fa[v] = u; deep[v] = deep[u] + 1; 
			val[v] = w;
			dis[v] = dis[u] + w;
			dfs(v);
			sze[u] += sze[v];
			if (!son[u] || sze[v] > sze[son[u]]) son[u] = v; 
		}
	}
	void gettop(int u, int tp) {
		in[u] = ++*in;
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
		*in = 0;
		dis[rt] = 0; 
		val[rt] = 0;
		dfs(rt);
		gettop(rt, rt);
		for (int i = 1; i <= n; ++i) {
			seg.update(1, 1, n, in[i], val[i]);
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
	int queryPath(int u, int v) {
		int res = 0;
		while (top[u] != top[v]) {
			if (deep[top[u]] < deep[top[v]]) swap(u, v);
			res = max(res, seg.query(1, 1, n, in[top[u]], in[u]));
			u = fa[top[u]];
		}
		if (u == v) return res;
		if (deep[u] > deep[v]) swap(u, v);
		res = max(res, seg.query(1, 1, n, in[son[u]], in[v]));
		return res;
	}
}hld;

int main() {
	int _T; scanf("%d", &_T);
	while (_T--) {
		scanf("%d", &n);
		G.init(n); seg.build(1, 1, n);
		for (int i = 1; i < n; ++i) {
			scanf("%d%d%d", e[i], e[i] + 1, e[i] + 2);
			G.addedge(e[i][0], e[i][1], e[i][2]);
			G.addedge(e[i][1], e[i][0], e[i][2]);
		}
		hld.init(1); 
		for (int i = 1; i < n; ++i) {
			if (hld.fa[e[i][1]] != e[i][0]) 
				swap(e[i][0], e[i][1]);
		}
		char op[20];
		while (scanf("%s", op)) {
			if (strcmp(op, "DONE") == 0) break;
			else if (strcmp(op, "CHANGE") == 0) {
				int i, v;
				scanf("%d%d", &i, &v);
				seg.update(1, 1, n, hld.in[e[i][1]], v);
			} else {
				int u, v;
				scanf("%d%d", &u, &v);
				printf("%d\n", hld.queryPath(u, v));
			}
		}
	}
	return 0;
}
