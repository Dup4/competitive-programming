#include <bits/stdc++.h>
using namespace std;

#define ll long long
const ll D = 1e18; 
const int p = 1e6 + 7; 
const int N = 3e4 + 10;
int n, q;
struct Num {
	ll a[3], v; 
	Num() {
		a[0] = a[1] = a[2] = 0;
		v = 0;
	}
	void scan() {
		string s; 
		cin >> s;
		v = 0;
	    reverse(s.begin(), s.end());	
		while (s.size() < 54) s += "0";
		reverse(s.begin(), s.end());
		cout << s << endl;
		for (int i = 0; i < 54; ++i) {
			a[i / 18] = a[i / 18] * 10 + s[i] - '0';
			a[i / 18] %= p;
		}
		for (int i = 0; i < 3; ++i) {
			v = v * (D % p) % p + (a[i] % p);
			v %= p;	
		}
	}
	void rev() {
		reverse(a, a + 3);
		v = 0;
		for (int i = 0; i < 3; ++i) {
			v = v * (D % p) % p + (a[i] % p);
			v %= p;
		}
	}
	bool operator < (const Num &other) const {
		for (int i = 0; i < 3; ++i) {
			if (a[i] != other.a[i])
				return a[i] < other.a[i];
		}
		return 1;
	}
}w[N];
vector <vector<int>> G;

int fa[N], deep[N], sze[N], son[N], top[N], in[N], fin[N], out[N], cnt;
void DFS(int u) {
	sze[u] = 1;
	for (int v : G[u]) {
		if (v == fa[u]) continue;
		fa[v] = u;
		deep[v] = deep[u] + 1;
		DFS(v);
		sze[u] += sze[v];
		if (!son[u] || sze[v] > sze[son[u]]) {
			son[u] = v;
		}
	}
}

void gettop(int u, int tp) {
	top[u] = tp;
	in[u] = ++cnt;
	fin[cnt] = u;
	out[u] = cnt;
	if (!son[u]) {
		return;
	}
	gettop(son[u], tp);
	for (int v : G[u]) {
		if (v == son[u] || v == fa[u]) continue;
		gettop(v, v);
	}
	out[u] = cnt;
}

struct SEG {
	struct node {
		Num x, y;
		int lazy;
		node() {
			x = Num(); y = Num();
			lazy = 0;
		}
		void add(int v) {
			if (v) swap(x, y);
			lazy ^= v;
		}
		node operator + (const node &other) const {
			node res = node();
			res.x = max(x, other.x);
			res.y = max(y, other.y);
			return res;
		}
	}t[N << 2], res;
	void build(int id, int l, int r) {
		t[id] = node();
		if (l == r) {
			t[id].x = w[fin[l]];
			t[id].y = t[id].x;
			t[id].y.rev();
			return;
		}
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
	}
	void pushdown(int id) {
		int &lazy = t[id].lazy;
		if (lazy) {
			t[id << 1].add(lazy);
			t[id << 1 | 1].add(lazy);
			lazy = 0;
		}
	}
	void update(int id, int l, int r, int ql, int qr) {
		if (l >= ql && r <= qr) {
			t[id].add(1);
			return;
		}
		int mid = (l + r) >> 1;
		pushdown(id);
		if (ql <= mid) update(id << 1, l, mid, ql, qr);
		if (qr > mid) update(id << 1 | 1, mid + 1, r, ql, qr);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	void query(int id, int l, int r, int ql, int qr) {
		if (l >= ql && r <= qr) {
			res = res + t[id];
			return;
		}
		int mid = (l + r) >> 1;
		pushdown(id);
		if (ql <= mid) query(id << 1, l, mid, ql, qr);
		if (qr > mid) query(id << 1 | 1, mid + 1, r, ql, qr);
	}
}seg;

void update(int u, int v) {
	while (top[u] != top[v]) {
		if (deep[top[u]] < deep[top[v]]) swap(u, v);
		seg.update(1, 1, n, in[top[u]], in[u]);
		u = fa[top[u]];
	}
	if (deep[u] > deep[v]) swap(u, v);
	seg.update(1, 1, n, in[u], in[v]);
}

void query(int u, int v) {
	while (top[u] != top[v]) {
		if (deep[top[u]] < deep[top[v]]) {
			swap(u, v);
		}
		seg.query(1, 1, n, in[top[u]], in[u]);
		u = fa[top[u]];
	}
	if (deep[u] > deep[v]) swap(u, v);
	seg.query(1, 1, n, in[u], in[v]);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	while (cin >> n) {
		G.clear(); G.resize(n + 1);
		cnt = 0;
		for (int i = 1; i <= n; ++i) son[i] = 0;
		for (int i = 1; i <= n; ++i) {
			w[i].scan();
		}
		for (int i = 1, u, v; i < n; ++i) {
			cin >> u >> v;
			G[u].push_back(v);
			G[v].push_back(u);
		}
		DFS(1); gettop(1, 1);
		seg.build(1, 1, n);
		cin >> q; int op, u, v;
		for (int qq = 1; qq <= q; ++qq) {
			cin >> op >> u;
			if (op == 1) {
				cin >> v;
				update(u, v);
			} else if (op == 2) {
				seg.update(1, 1, n, in[u], out[u]);
			} else {
				cin >> v;
				seg.res = SEG::node();
				query(u, v);
				cout << seg.res.x.v << "\n";
			}
		}
	}	
	return 0;
}
