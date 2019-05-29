#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
int n, m, D, a[N];
vector < vector <int> > G;

ll res;
int fa[N], deep[N], son[N], sze[N], top[N], p[N], cnt;
void DFS(int u) {
	sze[u] = 1;
	son[u] = 0;
	for (auto v : G[u]) {
		deep[v] = deep[u] + 1;
		fa[v] = u;
		DFS(v);
		sze[u] += sze[v];
		if (!son[u] || sze[v] > sze[son[u]]) {
			son[u] = v;
		}
	}
}
void gettop(int u, int tp) {
	p[u] = ++cnt;
	top[u]= tp;
	if (!son[u]) {
		return;
	}
	gettop(son[u], tp);
	for (auto v : G[u]) if (v != son[u]) {
		gettop(v, v);
	}
}

int query_lca(int u, int v) {
	while (top[u] != top[v]) {
		if (deep[top[u]] < deep[top[v]]) {
			swap(u, v);
		}
		u = fa[top[u]];
	}
	if (deep[u] > deep[v]) {
		swap(u, v);
	}
	return u;
}

struct SEG {
	int rt[N];
	struct node {
		int ls, rs; 
		ll cnt, sum;
		int lazy;
		node() {
			ls = rs = 0;
			cnt = sum = lazy = 0;
		}
		void up() {
			cnt = 0;
			sum = 0;
			lazy = 1; 
		}
		node (int ls, int rs, ll cnt, ll sum) : ls(ls), rs(rs), cnt(cnt), sum(sum) {
			lazy = 0;
		}
	}t[N * 50];
	int cnt;
	void init() {
		cnt = 0;
		t[0] = node();
		for (int i = 1; i <= n; ++i) {
			rt[i] = 0;
		}
	}
	void pushup(int id) {
		int ls = t[id].ls, rs = t[id].rs;
		t[id].cnt = t[ls].cnt + t[rs].cnt;  
		t[id].sum = t[ls].sum + t[rs].sum;
	}
	void pushdown(int id) {
		int &lazy = t[id].lazy;
		if (!lazy) return;
		int ls = t[id].ls, rs = t[id].rs;
		t[ls].up();
		t[rs].up();
		lazy = 0;
	}
	void update(int &id, int l, int r, int x, int val) {
		if (!id) id = ++cnt;
		t[id] = node();
		if (l == r) {
			t[id].cnt += val;
			t[id].sum += 1ll * val * l; 
			return;
		}
		int mid = (l + r) >> 1;
		pushdown(id); 
		if (x <= mid) update(t[id].ls, l, mid, x, val);
		else update(t[id].rs, mid + 1, r, x, val); 
		pushup(id);   
	}
	int merge(int u, int v) {
		if (!u || !v) return u | v;
		pushdown(u);
		pushdown(v);
		t[u].cnt += t[v].cnt;  
		t[u].sum += t[v].sum;
		if (t[u].ls | t[v].ls) {
			t[u].ls = merge(t[u].ls, t[v].ls);
		}
		if (t[u].rs | t[v].rs) {   
			t[u].rs = merge(t[u].rs, t[v].rs); 
		}
		return u;  
	}	
	void query(int id, int l, int r, int k) {
		if (!id || k <= 0) return;
		if (t[id].cnt <= k) {
			res += t[id].sum;
			t[id].cnt = 0;
			t[id].sum = 0;
			t[id].lazy = 1; 
			return;
		}
		if (l == r) {
			res += 1ll * k * l; 
			t[id].cnt -= k;
			t[id].sum -= 1ll * k * l;
			return;
		}
		int mid = (l + r) >> 1;
		pushdown(id);
		query(t[id].ls, l, mid, k - (t[id].rs ? t[t[id].rs].cnt : 0));
		query(t[id].rs, mid + 1, r, k);
	}
}seg;

void solve(int u) {  
	for (auto v : G[u]) {
		solve(v);
		seg.merge(seg.rt[u], seg.rt[v]);
	}
	seg.query(seg.rt[u], 1, D, a[u]);
}

void init() {
	cnt = 0;
	seg.init();
	G.clear();
	G.resize(n + 1);
	D = 10000;
	res = 0;
}
int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		init(); 
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
		}
		for (int i = 2; i <= n; ++i) {
			G[i / 2].push_back(i);
		}
		DFS(1); gettop(1, 1);
		for (int i = 1, u, v, c, w; i <= m; ++i) {
			scanf("%d%d%d%d", &u, &v, &c, &w);
			int lca = query_lca(u, v);
			seg.update(seg.rt[u], 1, D, w, c);
			seg.update(seg.rt[v], 1, D, w, c);
			seg.update(seg.rt[lca], 1, D, w, -c);
		}
		solve(1);
		printf("%lld\n", res);
	}
	return 0;
}
