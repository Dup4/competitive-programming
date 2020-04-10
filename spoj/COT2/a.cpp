#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
const int block = 400;
int n, m, q;
int arr[N], ans[N];
vector <vector<int>> G;

struct Hash {
	vector <int> a;
	int& operator[](int x) { return a[x - 1]; }
	int size() { return a.size(); }
	void init() { a.clear(); }
	void add(int x) { a.push_back(x); }
	void gao() { sort(a.begin(), a.end()); a.erase(unique(a.begin(), a.end()), a.end()); }
	int query(int x) { return lower_bound(a.begin(), a.end(), x) - a.begin() + 1; }	
}hs;

namespace Mo {
	int top[N], fa[N], deep[N], sze[N], son[N], in[N], out[N], ord[N];
	int cnt[N], res; 
	bool used[N];
	void dfs(int u)  {
		sze[u] = 1; son[u] = 0;
		for (auto &v : G[u]) if (v != fa[u]) {
			fa[v] = u;
			deep[v] = deep[u] + 1;
			dfs(v); 
			sze[u] += sze[v];
			if (son[u] == 0 || sze[v] > sze[son[u]])
				son[u] = v;
		}
	}
	void gettop(int u, int tp) {
		top[u] = tp;
		ord[++*ord] = u;
		in[u] = *ord;
		if (son[u]) gettop(son[u], tp);
		for (auto v : G[u]) if (v != fa[u] && v != son[u])
			gettop(v, v); 
		ord[++*ord] = u;
		out[u] = *ord;
	}
	int querylca(int u, int v) {
		while (top[u] != top[v]) {
			if (deep[top[u]] < deep[top[v]]) swap(u, v);
			u = fa[top[u]];
		}
		if (deep[u] > deep[v]) swap(u, v);
		return u;   
	}
	struct qnode {
		int l, r, id, lca;
		qnode(int l = 0, int r = 0, int id = 0, int lca = 0) : l(l), r(r), id(id), lca(lca) {}
		bool operator < (const qnode &r) const {
			int posl = l / block, posr = r.l / block;
			return posl == posr ? this->r < r.r : posl < posr;
		}
	}que[N];
	void update(int pos) {
		int x = ord[pos]; 
		if (used[x]) { //minus
			if (cnt[arr[x]] == 1) --res;
			--cnt[arr[x]];
		}
		else {
			if (cnt[arr[x]] == 0) ++res;  
			++cnt[arr[x]];
		}
		used[x] ^= 1; 	
	}
	void gao() {
		memset(used, 0, sizeof used);
		memset(cnt, 0, sizeof cnt);
		res = 0;  *ord = 0; deep[1] = 0; fa[1] = 1;
		dfs(1); gettop(1, 1); 
		for (int i = 1, u, v; i <= q; ++i) {
			scanf("%d%d", &u, &v);
			int lca = querylca(u, v);
			if (in[u] > in[v]) swap(u, v); 
			if (u == lca) que[i] = qnode(in[u], in[v], i, 0);
			else que[i] = qnode(out[u], in[v], i, lca);
		}
		sort(que + 1, que + 1 + q);
		for (int i = 1, l = 1, r = 0; i <= q; ++i) {
			for (; r < que[i].r; ++r) update(r + 1);
			for (; r > que[i].r; --r) update(r);
			for (; l < que[i].l; ++l) update(l);
			for (; l > que[i].l; --l) update(l - 1);
			ans[que[i].id] = res;
			//特判lca的贡献
			if (que[i].lca)
				if (cnt[arr[que[i].lca]] == 0) ++ans[que[i].id];
		}
	}
}

int main() {
	while (scanf("%d%d", &n, &q) != EOF) {
		G.clear(); G.resize(n + 1);
		hs.init();
		for (int i = 1; i <= n; ++i) {
			scanf("%d", arr + i);
			hs.add(arr[i]);
		}
		hs.gao();
		for (int i = 1; i <= n; ++i) arr[i] = hs.query(arr[i]);
		for (int i = 1, u, v; i < n; ++i) {
			scanf("%d%d", &u, &v); 
			G[u].push_back(v);
			G[v].push_back(u);
		}
		Mo::gao();
		for (int i = 1; i <= q; ++i) printf("%d\n", ans[i]);
	}
	return 0;
}
