#include <bits/stdc++.h>
using namespace std;
const int N = 8e4 + 10, M = 17;
int n, m, ce, q, a[N], fa[N][M], deep[N], lst; 
vector <vector<int>> G;

struct Hash {
	vector <int> a;
	void init() { a.clear(); }
	void add(int x) { a.push_back(x); }
	void gao() { sort(a.begin(), a.end()); a.erase(unique(a.begin(), a.end()), a.end()); }
	int get(int x) { return lower_bound(a.begin(), a.end(), x) - a.begin() + 1; }
}hs;

struct UFS {
	int fa[N], sze[N]; 
	void init(int n) { for (int i = 0; i <= n; ++i) fa[i] = i, sze[i] = 1; }
	int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
	void merge(int x, int y) { 
		x = find(x); y = find(y); 
		if (x != y) { 
			if (sze[x] > sze[y]) swap(x, y); 
			fa[x] = y;
			sze[y] += sze[x];
		}
	}
}ufs;

struct SEG {
	struct node {
		int ls, rs, sum;
		void init() { ls = rs = sum = 0; }
	}t[N * 300];
	int rt[N], tot; 
	void init() { memset(rt, 0, sizeof rt); tot = 0; t[0].init(); }
	int newnode() {
		++tot;
		t[tot].init();
		return tot;
	}
	void build(int &id, int l, int r) {
		id = newnode();
		if (l == r) return;
		int mid = (l + r) >> 1;
		build(t[id].ls, l, mid);
		build(t[id].rs, mid + 1, r);
	}
	void update(int &now, int pre, int l, int r, int pos, int v) {
		now = newnode();
		t[now] = t[pre];
		t[now].sum += v;
		if (l == r) return;
		int mid = (l + r) >> 1;
		if (pos <= mid) update(t[now].ls, t[pre].ls, l, mid, pos, v);
		else update(t[now].rs, t[pre].rs, mid + 1, r, pos, v);
	}
	int query(int x, int y, int lca, int falca, int l, int r, int k) {
		if (l == r) return l;
		int lsum = t[t[x].ls].sum + t[t[y].ls].sum - t[t[lca].ls].sum - t[t[falca].ls].sum;
		int mid = (l + r) >> 1;
		if (lsum >= k) {
			return query(t[x].ls, t[y].ls, t[lca].ls, t[falca].ls, l, mid, k);
		} else {
			return query(t[x].rs, t[y].rs, t[lca].rs, t[falca].rs, mid + 1, r, k - lsum); 
		}
	}
}seg;

void dfs(int u) {
	for (int i = 1; i < M; ++i) {
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
	}
	for (auto &v : G[u]) if (v != fa[u][0]) {
		deep[v] = deep[u] + 1;
		fa[v][0] = u;
		seg.update(seg.rt[v], seg.rt[u], 1, m, a[v], 1);
		dfs(v);
	}
}

int querylca(int u, int v) {
	if (deep[u] < deep[v]) swap(u, v);
	int deg = deep[u] - deep[v];
    for (int i = 0; i < M; ++i) {
		if ((deg >> i) & 1) {
			u = fa[u][i];
		}
	}	
	if (u == v) return u;
	for (int i = M - 1; i >= 0; --i) {
		if (fa[u][i] != fa[v][i]) {
			u = fa[u][i];
			v = fa[v][i];
		}
	}
	return fa[u][0];
}

int main() {
	int _T; scanf("%d", &_T);
	scanf("%d%d%d", &n, &ce, &q);
	G.clear(); G.resize(n + 1); ufs.init(n);
	hs.init(); lst = 0;  
	for (int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
		hs.add(a[i]);
	}	
	hs.gao(); m = hs.a.size();
	for (int i = 1; i <= n; ++i) a[i] = hs.get(a[i]);
	for (int i = 1, u, v; i <= ce; ++i) {
		scanf("%d%d", &u, &v);
		G[u].push_back(v);
		G[v].push_back(u); 
		ufs.merge(u, v);
	}	
	seg.init(); seg.build(seg.rt[0], 1, m);
	memset(deep, 0, sizeof deep); 
	for (int i = 1; i <= n; ++i) {
		if (deep[i] == 0) {
			deep[i] = 1;
			fa[i][0] = 0;
			seg.update(seg.rt[i], seg.rt[0], 1, m, a[i], 1); 
			dfs(i);
		}	
	}
	char op[10]; int x, y, z;
	for (int i = 1; i <= q; ++i) {
		scanf("%s", op);
		if (*op == 'Q') {
			scanf("%d%d%d", &x, &y, &z); 
			x ^= lst; y ^= lst; z ^= lst;
			int lca = querylca(x, y);
			lst = hs.a[seg.query(seg.rt[x], seg.rt[y], seg.rt[lca], seg.rt[fa[lca][0]], 1, m, z) - 1];
			printf("%d\n", lst);
		} else {
			scanf("%d%d", &x, &y);
			x ^= lst; y ^= lst;
			G[x].push_back(y);
			G[y].push_back(x);
			if (ufs.sze[ufs.find(x)] > ufs.sze[ufs.find(y)]) swap(x, y);
			ufs.merge(x, y);
			seg.update(seg.rt[x], seg.rt[y], 1, m, a[x], 1);
			deep[x] = deep[y] + 1;
			fa[x][0] = y;
			dfs(x);
		}
	}
	return 0;
}
