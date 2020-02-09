#include <bits/stdc++.h>
using namespace std;
using pII = pair<int, int>;
#define fi first
#define se second
const int N = 5e5 + 10, M = 20, INF = 0x3f3f3f3f;
int n, q, rt; 

struct E { int to, nx, w; }e[N << 1]; int h[N]; 
void initE(int n) { for (int i = 0; i <= n; ++i) h[i] = 0; }
void addedge(int u, int v, int w = 0) { e[++*h] = { v, h[u], w }; h[u] = *h;}

struct RMQ {
	pII Min[N << 1][M]; 
	int mm[N << 1]; 
	void init(int n, pII *a) {
		mm[0] = -1;
		for (int i = 1; i <= n; ++i) {
			mm[i] = ((i & (i - 1)) == 0) ? mm[i - 1] + 1 : mm[i - 1];
			Min[i][0] = a[i];
		}
		for (int j = 1; j <= mm[n]; ++j) {
			for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
				Min[i][j] = min(Min[i][j - 1], Min[i + (1 << (j - 1))][j - 1]);
			}
		}
	}
	pII queryMin(int x, int y) { 
		if (x > y) swap(x, y);
		int k = mm[y - x + 1];
		return min(Min[x][k], Min[y - (1 << k) + 1][k]);
	}
}st;

struct LCA {
	pII rmq[N << 1];
	int low[N], cnt;
	void dfs(int u, int fa, int dep) {
		rmq[++cnt] = pII(dep, u);
		low[u] = cnt;
		for (int i = h[u]; i; i = e[i].nx) {
			int v = e[i].to;   
			if (v == fa) continue;	
			dfs(v, u, dep + 1);
			rmq[++cnt] = pII(dep, u);
		}
	}
	void init(int rt, int n) {
		cnt = 0;
		dfs(rt, rt, 0);
		st.init(2 * n - 1, rmq);
	}
	int querylca(int u, int v) { return st.queryMin(low[u], low[v]).se; }
}lca;

int main() {
	while (scanf("%d%d%d", &n, &q, &rt) != EOF) {
		initE(n);
		for (int i = 1, u, v; i < n; ++i) {
			scanf("%d%d", &u, &v);
			addedge(u, v);
			addedge(v, u);
		}
		lca.init(rt, n);
		for (int i = 1, u, v; i <= q; ++i) {
			scanf("%d%d", &u, &v);
			printf("%d\n", lca.querylca(u, v));
		}
	}
	return 0;
}
