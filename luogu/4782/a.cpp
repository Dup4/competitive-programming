#include <bits/stdc++.h>
using namespace std;
const int N = 4e6 + 10;
int n, m;

// G 原图 T 逆图
struct Graph {
	struct E { int to, nx, w; }e[N << 1]; int h[N], cntSCC;
	void init(int n) { for (int i = 0; i <= n; ++i) h[i] = -1; cntSCC = -1; }
	void addedge(int u, int v, int w = 0) { e[++cntSCC] = { v, h[u], w}; h[u] = cntSCC; } 
}G, T;

struct Kosaraju {
	bool mark[2][N];
	int sta[N], setNum[N], Belong[N], cntSCC;
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
		work(n * 2);
		for (int i = 1; i <= n; ++i) {
			if (Belong[i] == Belong[i + n]) {
				puts("IMPOSSIBLE");
				return;
			}
		}
		puts("POSSIBLE");
		for (int i = 1; i <= n; ++i) {
			printf("%d%c", (Belong[i] > Belong[i + n]), " \n"[i == n]);
		}
	}
}kosaraju;

int main() {
	scanf("%d%d", &n, &m);
	G.init(n * 2); T.init(n * 2);
	for (int i = 1, u, v, a, b, _u, _v; i <= m; ++i) {
		scanf("%d%d%d%d", &u, &a, &v, &b);
		_u = u + n * (a & 1), _v = v + n * (b ^ 1);
		G.addedge(_u, _v);
		T.addedge(_v, _u);
		_u = v + n * (b & 1), _v = u + n * (a ^ 1);
		G.addedge(_u, _v);
		T.addedge(_v, _u);
	}
	kosaraju.gao(n);
	return 0;
}
