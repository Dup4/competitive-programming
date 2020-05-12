#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int n, m, q;

// G 原图 T 逆图
struct Graph {
	struct E { int to, nx, w; }e[N << 1]; int h[N], cntSCC;
	void init(int n) { for (int i = 0; i <= n; ++i) h[i] = -1; cntSCC = -1; }
	void addedge(int u, int v, int w = 0) { e[++cntSCC] = { v, h[u], w}; h[u] = cntSCC; } 
}G, T;

struct UFS {
	int fa[N], rk[N]; 
	void init(int n) {
		memset(fa, 0, sizeof (fa[0]) * (n + 5));
		memset(rk, 0, sizeof (rk[0]) * (n + 5));
	}
	int find(int x) { return fa[x] == 0 ? x : fa[x] = find(fa[x]); }
	bool merge(int x, int y) {
		int fx = find(x), fy = find(y);
		if (fx != fy) {
			if (rk[fx] > rk[fy]) swap(fx, fy);
			fa[fx] = fy;
			if (rk[fx] == rk[fy]) ++rk[fy];
			return true;
		}
		return false;
	}
	bool same(int x, int y) { return find(x) == find(y); }
}ufs;

struct Kosaraju {
	bool mark[2][N];
	int sta[N], setNum[N], Belong[N], cntSCC, dOut[N];
	//setNum[i] 第i个SCC的点数
	//Belong[i] 点i属于哪个SCC
	void dfs(int u) {
		mark[0][u] = 1;
		for (int i = G.h[u]; ~i; i = G.e[i].nx) {
			int v = G.e[i].to;
			if (!mark[0][v]) 
				dfs(v);
		}
		sta[++*sta] = u;
	}
	void dfs1(int u) {
		mark[1][u] = 1;
		++setNum[cntSCC];
		Belong[u] = cntSCC;
		for (int i = T.h[u]; ~i; i = T.e[i].nx) {
			int v = T.e[i].to;
			if (!mark[1][v])
				dfs1(v);
		}
	}
	void work(int n) {
		memset(mark[0], 0, sizeof (mark[0][0]) * (n + 5));
		memset(mark[1], 0, sizeof (mark[1][0]) * (n + 5));
		memset(setNum, 0, sizeof (setNum[0]) * (n + 5));
		*sta = 0; cntSCC = 0;
		for (int i = 1; i <= n; ++i) 
			if (!mark[0][i])
				dfs(i);
		for (int i = *sta; i >= 1; --i) {
			if (!mark[1][sta[i]]) {
				++cntSCC;
				dfs1(sta[i]);
			}
		}
	}
	void gao(int n) {
		work(n);
		scanf("%d", &q);
		for (int i = 1, u, v; i <= q; ++i) {
			scanf("%d%d", &u, &v);
			puts(Belong[u] == Belong[v] ? "Yes" : "No");
		}
	}
}kosaraju;

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		G.init(n); T.init(n);
		for (int i = 1, u, v; i <= m; ++i) {
			scanf("%d%d", &u, &v);
			G.addedge(u, v);
			T.addedge(v, u);
		}
		kosaraju.gao(n);
	}
	return 0;
}
