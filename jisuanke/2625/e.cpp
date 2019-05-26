#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n, q;
int a[N];
vector < vector <int> > G;   

int fa[N], deep[N], sze[N], son[N], top[N], p[N], cnt;
void DFS(int u) {
	sze[u] = 1;
	son[u] = 0;
	for (auto v : G[u]) if (v != fa[u]) {
		fa[v] = u;
		deep[v] = deep[u] + 1;
		DFS(v);
		sze[u] += sze[v];
		if (!son[u] || sze[v] > sze[son[u]]) {
			son[u] = v;
		}
	}
}
void gettop(int u, int sp) {
	top[u] = sp;
	p[u] = ++cnt;
	if (!son[u]) {
		return;
	}
	gettop(son[u], sp);
	for (auto v : G[u]) if (v != fa[u] && v != son[u]) {
		gettop(v, v);
	}
}

struct SEG {
	struct node {
		int And, Or, sum, cnt; 
		node () {
			And = -1;
			Or = 0;
			sum = 0;
			cnt = 0;
		}
		node (int And, int Or, int sum) : And(And), Or(Or), sum(sum) {
			cnt = 0;
		}
		void addAnd(int x) {
			sum &= x;
			Or &= x;
			And &= x;
		}
		void addOr(int x) {
			if (cnt & 1) {
				sum |= x;
			} else {
				sum &= (~x);
			}
			And |= x;  
			Or |= x; 
		}
		node operator + (const node &other) const {
			node res = node();
			res.sum = sum ^ other.sum;
			res.cnt = cnt + other.cnt; 
			return res; 
		}
	}t[N << 2];
	void build(int id, int l, int r) {
		t[id] = node();
		if (l == r) {
			t[id].sum = a[l];
			t[id].cnt = 1;
			return;
		}
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	void pushdown(int id) {
		int &And = t[id].And;
		int &Or = t[id].Or;
		t[id << 1].addAnd(And);
		t[id << 1].addOr(Or);
		t[id << 1 | 1].addAnd(And);
		t[id << 1 | 1].addOr(Or);
		And = -1;
		Or = 0;
	}
	void upAnd(int id, int l, int r, int ql, int qr, int x) {
		if (l >= ql && r <= qr) {
			t[id].addAnd(x);
			return;
		}
		int mid = (l + r) >> 1;
		pushdown(id);
		if (ql <= mid) upAnd(id << 1, l, mid, ql, qr, x);
		if (qr > mid) upAnd(id << 1 | 1, mid + 1, r, ql, qr, x);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	void upOr(int id, int l, int r, int ql, int qr, int x) {
		if (l >= ql && r <= qr) {
			t[id].addOr(x);
			return;
		}
		int mid = (l + r) >> 1;
		pushdown(id);
		if (ql <= mid) upOr(id << 1, l, mid, ql, qr, x);
		if (qr > mid) upOr(id << 1 | 1, mid + 1, r, ql, qr, x);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	int query(int id, int l, int r, int ql, int qr) {
		if (l >= ql && r <= qr) {
			return t[id].sum;
		}
		int mid = (l + r) >> 1;
		pushdown(id);
		int res = 0;
		if (ql <= mid) res ^= query(id << 1, l, mid, ql, qr);
		if (qr > mid) res ^= query(id << 1 | 1, mid + 1, r, ql, qr);
		return res;
	}
}seg;

void updateOr(int u, int v, int t) {
	while (top[u] != top[v]) {
		if (deep[top[u]] < deep[top[v]]) {
			swap(u, v);
		}
		seg.upOr(1, 1, n, p[top[u]], p[u], t);
		u = fa[top[u]];
	}
	if (deep[u] > deep[v]) {
		swap(u, v);
	}
	seg.upOr(1, 1, n, p[u], p[v], t);
}


void updateAnd(int u, int v, int t) {
	while (top[u] != top[v]) {
		if (deep[top[u]] < deep[top[v]]) {
			swap(u, v);
		}
		seg.upAnd(1, 1, n, p[top[u]], p[u], t);
		u = fa[top[u]];
	}
	if (deep[u] > deep[v]) {
		swap(u, v);
	}
	seg.upAnd(1, 1, n, p[u], p[v], t);
}

int query(int u, int v) {
	int res = 0;
	while (top[u] != top[v]) {
		if (deep[top[u]] < deep[top[v]]) {
			swap(u, v);
		}
		res ^= seg.query(1, 1, n, p[top[u]], p[u]);
		u = fa[top[u]];
	}
	if (deep[u] > deep[v]) {
		swap(u, v);
	}
	res ^= seg.query(1, 1, n, p[u], p[v]);
	return res;
}

int main() {
	while (scanf("%d%d", &n, &q) != EOF) {
		G.clear();
		G.resize(n + 1);
		cnt = 0;
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
		}
		for (int i = 1, u, v; i < n; ++i) {
			scanf("%d%d", &u, &v);
			G[u].push_back(v);
			G[v].push_back(u);
		}
		DFS(1);
		gettop(1, 1);
		seg.build(1, 1, n);
		int op, s, t;
		for (int i = 1; i <= q; ++i) {
			scanf("%d%d%d", &op, &s, &t);
			switch(op) {
				case 1 :
					updateOr(1, s, t);
					break;
				case 2 :
					updateAnd(1, s, t);
					break;
				case 3 :
					puts((query(1, s) ^ t) == 0 ? "NO" : "YES");
					break;
				default :
					assert(0);
			}
		}	
	}
	return 0;
}
