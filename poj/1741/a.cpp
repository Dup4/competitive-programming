#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
#define ll long long
const int N = 1e4 + 10;
int n, k;

struct Graph {
	struct E { int to, nx, w; }e[N << 1]; int h[N], cnt;
	void init(int n) { for (int i = 0; i <= n; ++i) h[i] = -1; cnt = -1; }
	void addedge(int u, int v, int w = 0) { e[++cnt] = { v, h[u], w}; h[u] = cnt; } 
}G;

namespace DCTree {
	int rt, sum, vis[N];
	int sze[N], f[N];
	int dist[N], d[N]; ll res;
	void getrt(int u, int fa) {
		sze[u] = 1, f[u] = 0;
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
		d[++*d] = dist[u];
		for (int i = G.h[u]; ~i; i = G.e[i].nx) {
			int v = G.e[i].to, w = G.e[i].w;
			if (v == fa || vis[v]) continue;
			dist[v] = dist[u] + w;
			getdeep(v, u); 
		}
	}
	ll calc(int u, int cost) {
		dist[u] = cost; *d = 0;
		getdeep(u, 0);
		sort(d + 1, d + 1 + *d); 
		ll res = 0;
		for (int i = 1; i < *d; ++i) {
			if (k - d[i] < d[i]) break;  
			int pos = upper_bound(d + 1, d + 1 + d[0], k - d[i]) - d - 1;
			res += pos - i;
		}
		return res; 
	}
	void solve(int u) {
		res += calc(u, 0);
		vis[u] = 1;
		for (int i = G.h[u]; ~i; i = G.e[i].nx) {
			int v = G.e[i].to, w = G.e[i].w;
			if (vis[v]) continue;
			res -= calc(v, w);
			sum = f[0] = sze[v]; rt = 0;
			getrt(v, 0);
			solve(rt);
		}
	}
	ll gao() {
		res = 0;
		memset(vis, 0, sizeof vis);
		sum = f[0] = n; rt = 0;	
		getrt(1, 0);
		solve(rt);
		return res;
	}
};

int main() {
	while (scanf("%d%d", &n, &k), n || k) {
		G.init(n);
		for (int i = 1, u, v, w; i < n; ++i) {
			scanf("%d%d%d", &u, &v, &w);
			G.addedge(u, v, w);
			G.addedge(v, u, w);
		}
		printf("%lld\n", DCTree::gao());
	}
	return 0;
}
