#include <bits/stdc++.h>
using namespace std;
const int N = 5e4 + 10;
int n, m, val[N * 18]; 

struct SEG { 
	int t[N * 53];
	int merge(int a, int b) { return val[a] > val[b] ? a : b; }
	void build(int id, int l, int r) {
		if (l == r) { 
			t[id] = l;
			return;
		}
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
		t[id] = merge(t[id << 1], t[id << 1 | 1]);
	}
	int query(int id, int l, int r, int ql, int qr) { 
		if (l >= ql && r <= qr) return t[id];
		int mid = (l + r) >> 1;
		if (qr <= mid) return query(id << 1, l, mid, ql, qr);
		if (ql > mid) return query(id << 1 | 1, mid + 1, r, ql, qr);
		return merge(query(id << 1, l, mid, ql, qr), query(id << 1 | 1, mid + 1, r, ql, qr));
	}
}seg;

struct E { 
	int l, r, pos, v, add; 
	bool operator < (const E &other) const { return v < other.v; } 
}; 
vector <E> vec;

struct Graph {
	struct E { int to, nx, w; }e[N << 1]; int h[N], cnt;
	void init(int n) { for (int i = 0; i <= n; ++i) h[i] = -1; cnt = -1; }
	void addedge(int u, int v, int w = 0) { e[++cnt] = { v, h[u], w}; h[u] = cnt; } 
}G;

namespace DCTree {
	int sum, rt, vis[N]; 
	int sze[N], f[N];
	int dist[N];
	int L, R, cnt;
	void getrt(int u, int fa) {
		f[u] = 0, sze[u] = 1;
		for (int i = G.h[u]; ~i; i = G.e[i].nx) {
			int v = G.e[i].to;
		 	if (v == fa || vis[v]) continue;	
			getrt(v, u); 
			sze[u] += sze[v];
			f[u] = max(f[u], sze[v]);
		}
		f[u] = max(f[u], sum - sze[u]);
		if (f[u] < f[rt]) rt = u;
	}
	void getdeep(int u, int fa) {
		vec.push_back({L, R, 0, 0, dist[u]}); 
		val[++cnt] = dist[u]; 	
		for (int i = G.h[u]; ~i; i = G.e[i].nx) {
			int v = G.e[i].to, w = G.e[i].w;
			if (v == fa || vis[v]) continue;
			dist[v] = dist[u] + w;
			getdeep(v, u);  
		}
	}
	void solve(int u) {
		vis[u] = 1; 
		val[++cnt] = 0; L = R = cnt;
		for (int i = G.h[u]; ~i; i = G.e[i].nx) {
			int v = G.e[i].to, w = G.e[i].w;
			if (vis[v]) continue; 
			dist[v] = w; 
			getdeep(v, u); 
			R = cnt;
		}
		for (int i = G.h[u]; ~i; i = G.e[i].nx) {
			int v = G.e[i].to;
		 	if (vis[v]) continue;	
			sum = f[0] = sze[v]; rt = 0;
			getrt(v, 0);
			solve(rt);
		}
	}
	priority_queue <E> pq;
	void extend(E tmp) {
		if (tmp.l > tmp.r) return;
		tmp.pos = seg.query(1, 1, cnt, tmp.l, tmp.r);
		tmp.v = val[tmp.pos] + tmp.add;
		pq.push(tmp);
	}
	void gao() {
		cnt = 0; L = R = 0; 
		memset(vis, 0, sizeof vis);
		sum = f[0] = n; rt = 0;
		getrt(1, 0);
		solve(rt);
		while (!pq.empty()) pq.pop();
		seg.build(1, 1, cnt);	
		for (int i = 0; i < (int)vec.size(); ++i) {
			extend({vec[i].l, vec[i].r, 0, 0, vec[i].add});
		}
		while (m--) {
			E top = pq.top(); pq.pop();
			printf("%d\n", top.v);
			extend({top.l, top.pos - 1, 0, 0, top.add});
		    extend({top.pos + 1, top.r, 0, 0, top.add});	
		}
	}
};

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		G.init(n);
		vec.clear();
		for (int i = 1, u, v, w; i < n; ++i) {
			scanf("%d%d%d", &u, &v, &w);
			G.addedge(u, v, w);
			G.addedge(v, u, w);
		}
		DCTree::gao();
	}
	return 0;
}
