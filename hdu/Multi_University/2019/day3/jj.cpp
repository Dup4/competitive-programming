#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
const ll p = 1e9 + 7;
int n, q, f[N], y[N];
vector <vector<int>> G;
ll Y[N], Y2[N], Y3[N];     
template <class T1, class T2>
void add(T1 &x, T2 y) {
	x += y;
	if (x >= p) x -= p;  
}

int fa[N], deep[N], sze[N], son[N], top[N], in[N], fin[N], out[N], cnt;
void DFS(int u) {
	sze[u] = 1;
	for (auto v : G[u]) if (v != fa[u]) {
		fa[v] = u;
		Y[v] = (Y[u] + y[v]) % p;
		Y2[v] = (Y2[u] + y[v]) % p;
		Y3[v] = (Y3[v] + y[u]) % p;
		deep[v] = deep[u] + 1;
		DFS(v);
		sze[u] += sze[v];
		if (!son[u] || sze[u] > sze[son[u]]) {
			son[u] = v;
		}
	}
}

void gettop(int u, int tp) {
	top[u] = tp;
	in[u] = ++cnt;
	fin[cnt] = u;
	if (!son[u]) {
		out[u] = cnt;
		return;
	}
	gettop(son[u], tp);
	for (auto v : G[u]) if (v != fa[u] && v != son[u]) {
		gettop(v, v);
	}
	out[u] = cnt;
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


struct SEG {
	struct node {
		ll F, lazy, Y[2], Fy[2]; int cnt;    
		node() {
			F = lazy = 0;
			Fy[0] = Fy[1] = Y[0] = Y[1] = 0;
			cnt = 0;
		}
		void add(ll x) {
			(F += x * cnt % p) %= p;
			lazy = (lazy + x) % p;
			for (int i = 0; i < 2; ++i) {
				Fy[i] = (Fy[i] + Y[i] * x % p) % p;
			}
		}
		node operator + (const node &other) const {
			node res = node();
			res.cnt = cnt + other.cnt;
			for (int i = 0; i < 2; ++i) {
				res.Y[i] = (Y[i] + other.Y[i]) % p;
				res.Fy[i] = (Fy[i] + other.Fy[i]) % p;
			}
			return res;
		}
	}t[N << 2], S, T, lca; 
	void build(int id, int l, int r) {
		t[id] = node();
		if (l == r) {
			t[id].cnt = 1;
			t[id].Y[0] = Y2[fin[l]];
			t[id].Y[1] = Y3[fin[l]];
			return;
		}
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	void pushdown(int id) {
		ll &lazy = t[id].lazy;
		if (!lazy) return;
		t[id << 1].add(lazy);
		t[id << 1 | 1].add(lazy);
		lazy = 0;
	}
	void update(int id, int l, int r, int ql, int qr, ll x) {
		if (l >= ql && r <= qr) {
			t[id].add(x);
			return;
		}
		int mid = (l + r) >> 1;
		pushdown(id);
		if (ql <= mid) update(id << 1, l, mid, ql, qr, x);
		if (qr > mid) update(id << 1 | 1, mid + 1, r, ql, qr, x);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	node query(int id, int l, int r, int pos) {
		if (l == r) return t[id];
		int mid = (l + r) >> 1;
		pushdown(id);
		if (pos <= mid) return query(id << 1, l, mid, pos);
		else return query(id << 1 | 1, mid + 1, r, pos);
	}
}seg;

void init() {
	G.clear(); G.resize(n + 1);
	for (int i = 1; i <= n; ++i) son[i] = 0;
	cnt = 0;
}
int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n); init(); 
		for (int i = 1; i <= n; ++i) scanf("%d", f + i);
		for (int i = 1; i <= n; ++i) scanf("%d", y + i);
		for (int i = 1, u, v; i < n; ++i) {
			scanf("%d%d", &u, &v);
			G[u].push_back(v);
			G[v].push_back(u);
		}
		Y[1] = y[1]; 
		Y2[1] = y[1];
		DFS(1); 
		gettop(1, 1);
		seg.build(1, 1, n);
		for (int i = 1; i <= n; ++i) {
			seg.update(1, 1, n, in[i], out[i], f[i]);
		}
		scanf("%d", &q);
		int op, s, t, x, c, v;
		while (q--) {
			scanf("%d", &op);
			if (op == 1) {
				scanf("%d%d%d", &s, &t, &x);
				ll res = 0, Ly, Ry, F, Fy;
				int lca = querylca(s, t);
				seg.S = seg.query(1, 1, n, in[s]);
				seg.T = seg.query(1, 1, n, in[t]);
				seg.lca = seg.query(1, 1, n, in[lca]); 
				//右边下去的贡献
				F = (seg.T.F - seg.lca.F + f[lca] + p) % p;   
				Fy = (seg.T.Fy[1] - seg.lca.Fy[1] + 1ll * f[lca] * (Y[lca] - y[lca] + p) % p + p) % p;
				cout << F << " " << Fy << endl;
				Ly = Y[s] - Y[lca]; 
				add(res, F * x % p);
				add(res, (p - F * Ly % p) % p);
				add(res, (p - Fy) % p);
				add(res, F * (Y[lca] - y[lca] + p) % p);
				
				cout << res << endl;
				//左边上去的贡献
				Ry = Y[t] - Y[lca] + y[lca];
				F = (seg.S.F - seg.lca.F + p) % p;
				Fy = (seg.S.Fy[0] - seg.lca.Fy[0] + p) % p;
				add(res, F * Ry % p);
				add(res, Fy);
				add(res, (p - (F * (Y[lca] - y[lca] + p) % p)) % p);
				ll remindx = (x - Y[s] - Y[t] + 2ll * Y[lca] - 2ll * y[lca] + p) % p;
				add(res, F * remindx % p);
				printf("%lld\n", res);
			} else {
				scanf("%d%d", &c, &v);
				seg.update(1, 1, n, in[c], out[c], p - f[c]);
				f[c] = v;
				seg.update(1, 1, n, in[c], out[c], f[c]);
			}
		}
	}
	return 0;
}
