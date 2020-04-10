#include <bits/stdc++.h>
using namespace std;
const int N = 4e6 + 10;
int n, m;

struct Graph {
	struct E { int to, nx, w; }e[N << 1]; int h[N], cntSCC;
	void init(int n) { for (int i = 0; i <= n; ++i) h[i] = -1; cntSCC = -1; }
	void addedge(int u, int v, int w = 0) { e[++cntSCC] = { v, h[u], w}; h[u] = cntSCC; } 
}G;

struct Tarjan {
	//Low[i] 点i第一次访问的时间戳
	//DFN[i] 点i能访问到的点中的Low的最小值
	//Belong[i] 点i属于哪个scc
	//num[i] 第i个scc有几个点
	int Low[N], DFN[N], sta[N], Belong[N], num[N], cntSCC; bool Insta[N];
	void dfs(int u) {
		Low[u] = DFN[u] = ++*Low;
		sta[++*sta] = u;
		Insta[u] = 1;
		for (int i = G.h[u]; ~i; i = G.e[i].nx) {
			int v = G.e[i].to;
			if (!DFN[v]) {
				dfs(v);
				Low[u] = min(Low[u], Low[v]);
			} else if (Insta[v])
				Low[u] = min(Low[u], DFN[v]); 
		}
		if (Low[u] == DFN[u]) {
			++cntSCC;
			int v;
			do {
				v = sta[(*sta)--];
				Insta[v] = 0;
				Belong[v] = cntSCC;
				++num[cntSCC];
			} while (v != u);
		}
	}
	void work(int n) {
		memset(DFN, 0, sizeof (DFN[0]) * (n + 10));
		memset(Insta, 0, sizeof (Insta[0]) * (n + 10));
		memset(num, 0, sizeof (num[0]) * (n + 10));
		cntSCC = *sta = *Low = 0;
		for (int i = 1; i <= n; ++i) if (!DFN[i]) dfs(i);
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
		//i 正 i + n 负，输出拓扑序大的点的决策
		for (int i = 1; i <= n; ++i) {
			printf("%d%c", (Belong[i] < Belong[i + n]), " \n"[i == n]);
		}
	}
}tarjan;

int main() {
	scanf("%d%d", &n, &m);
	G.init(n * 2); 
	for (int i = 1, u, v, a, b, _u, _v; i <= m; ++i) {
		scanf("%d%d%d%d", &u, &a, &v, &b);
		_u = u + n * (a & 1), _v = v + n * (b ^ 1);
		G.addedge(_u, _v);
		_u = v + n * (b & 1), _v = u + n * (a ^ 1);
		G.addedge(_u, _v);
	}
	tarjan.gao(n);
	return 0;
}
