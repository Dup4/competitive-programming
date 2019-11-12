#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 10;
const ll INF = 0x3f3f3f3f3f3f3f3f;
vector <vector<int>> G;
int n, q, v[N], fa[N], deep[N], sze[N], son[N], top[N], in[N], fin[N], bot[N]; 
ll f[N][2];

struct Matrix {
	ll a[2][2];
	void init() { a[0][0] = a[1][1] = 0; a[0][1] = a[1][0] = -INF; }
	ll* operator[] (int x) { return a[x]; } 
	Matrix operator * (Matrix b) {
		Matrix res;
		res[0][0] = max(a[0][0] + b[0][0], a[0][1] + b[1][0]);
		res[0][1] = max(a[0][0] + b[0][1], a[0][1] + b[1][1]);
		res[1][0] = max(a[1][0] + b[0][0], a[1][1] + b[1][0]);
		res[1][1] = max(a[1][0] + b[0][1], a[1][1] + b[1][1]);
		return res;
	};
}bk[N];

struct SEG {
	Matrix t[N << 2];
	void build(int id, int l, int r) {
		if (l == r) {
			int u = fin[l]; ll g[2] = {0, v[u]};
			for (auto &v : G[u]) if (v != fa[u] && v != son[u]) {
				g[0] += max(f[v][0], f[v][1]);
				g[1] += f[v][0];
			}
			bk[l] = t[id] = {g[0], g[0], g[1], -INF};
			return;
		}
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
		t[id] = t[id << 1] * t[id << 1 | 1];
	}
	void modify(int id, int l, int r, int pos) {
		if (l == r) {
			t[id] = bk[l];
			return;
		}
		int mid = (l + r) >> 1;
		if (pos <= mid) modify(id << 1, l, mid, pos);
		else modify(id << 1 | 1, mid + 1, r, pos);
		t[id] = t[id << 1] * t[id << 1 | 1];  
	}
	Matrix query(int id, int l, int r, int ql, int qr) {
		if (l == r) return t[id];
		int mid = (l + r) >> 1;
		Matrix res; res.init();
		if (ql <= mid) res = res * query(id << 1, l, mid, ql, qr);
		if (qr > mid) res = res * query(id << 1 | 1, mid + 1, r, ql, qr);
		return res;
	}
}seg;

namespace Tree {
	void dfs(int u) {
		sze[u] = 1; son[u] = 0;
		for (auto &v : G[u]) if (v != fa[u]) {
			fa[v] = u;
			deep[v] = deep[u] + 1;
			dfs(v);
			sze[u] += sze[v];
			if (!son[u] || sze[v] > sze[son[u]])
				son[u] = v;
		}
	}
	//in[u] - bot[u] 表示的是一条重链的dfs序的范围
	void gettop(int u, int tp) {
		top[u] = tp;
		in[u] = ++*in;
		fin[*in] = u; 
		if (son[u]) {
			gettop(son[u], tp);
			bot[u] = bot[son[u]];
		} else {
			bot[u] = *in; 
		}
		for (auto &v : G[u]) if (v != fa[u] && v != son[u]) 
			gettop(v, v);
	}
	void getInitAns(int u) {
		f[u][0] = 0, f[u][1] = v[u];
		for (auto &v : G[u]) if (v != fa[u]) {
			getInitAns(v);
			f[u][0] += max(f[v][0], f[v][1]);
			f[u][1] += f[v][0];
		}
	}
	void init() {
		*in = 0; fa[1] = 0; deep[1] = 0;
		dfs(1); 
		gettop(1, 1);
		getInitAns(1);
		seg.build(1, 1, n);
	}
	void modify(int u, int w) {
		bk[in[u]][1][0] += w - v[u]; v[u] = w;
		while (1) {
			Matrix a = seg.query(1, 1, n, in[top[u]], bot[top[u]]);
			seg.modify(1, 1, n, in[u]);
			Matrix b = seg.query(1, 1, n, in[top[u]], bot[top[u]]);
			u = fa[top[u]]; if (!u) break; 
			int x = in[u];
			ll g[2] = {a[0][0], a[1][0]}, f[2] = {b[0][0], b[1][0]};
			bk[x][0][0] = bk[x][0][1] = bk[x][0][0] + max(f[0], f[1]) - max(g[0], g[1]);
			bk[x][1][0] = bk[x][1][0] + f[0] - g[0];
		}
	} 
};

int main() {
	while (scanf("%d%d", &n, &q) != EOF) {
		G.clear(); G.resize(n + 1);
		for (int i = 1; i <= n; ++i) scanf("%d", v + i);
		for (int i = 1, u, v; i < n; ++i) {
			scanf("%d%d", &u, &v);
			G[u].push_back(v);
			G[v].push_back(u);
		}
		Tree::init();
		while (q--) {
			int u, w;
			scanf("%d%d", &u, &w);
			Tree::modify(u, w);
			Matrix res = seg.query(1, 1, n, in[1], bot[1]);
			printf("%lld\n", max(res[0][0], res[1][0]));
		}
	}
	return 0;
}
