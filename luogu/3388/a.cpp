#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
int n, m;
struct Edge { int v, nx, cut; }e[N << 1]; int h[N], tot;
inline void addedge(int u, int v) { e[tot] = {v, h[u], 0}; h[u] = tot++; }
struct Tarjan {
	//Low[i] 点i第一次访问的时间戳
	//DFN[i] 点i能访问到的点中的Low的最小值
	//Belong[i] 点i属于哪个scc
	//num[i] 第i个scc有几个点
	int Low[N], DFN[N], sta[N], Belong[N], num[N], add_block[N], scc, bridge; bool Insta[N];
	int d_in[N], d_out[N]; 
	void dfs(int u, int pre) {
		Low[u] = DFN[u] = ++*Low;
		sta[++*sta] = u;
		Insta[u] = 1;
		int son = 0;  
		for (int i = h[u]; ~i; i = e[i].nx) {
			int v = e[i].v;
			if (v == pre) continue;
			if (!DFN[v]) {
				++son;
				dfs(v, u);
				Low[u] = min(Low[u], Low[v]);
				//桥
				if (Low[v] > DFN[u]) {
					++bridge;
					e[i].cut = 1;
					e[i ^ 1].cut = 1; 
				}
				if (u != pre && Low[v] >= DFN[u]) {
					cut[u] = 1;
					++add_block[u];
				}
			} else if (Insta[v])
				Low[u] = min(Low[u], DFN[v]); 
		}
		if (Low[u] == DFN[u]) {
			++scc;
			int v;
			do {
				v = sta[(*sta)--];
				Insta[v] = 0;
				Belong[v] = scc;
				++num[scc];
			} while (v != u);
		}
	}
	void gao(int n) {
		memset(DFN, 0, sizeof (DFN[0]) * (n + 10));
		memset(Insta, 0, sizeof (Insta[0]) * (n + 10));
		memset(num, 0, sizeof (num[0]) * (n + 10));
		scc = *sta = *Low = 0;
		for (int i = 1; i <= n; ++i) if (!DFN[i]) dfs(i);
	}
	void gogogo() {
		memset(d_in, 0, sizeof (d_in[0]) * (scc + 10));
		memset(d_out, 0, sizeof (d_out[0]) * (scc + 10));
		for (int u = 1; u <= n; ++u) {
			for (auto &v : G[u]) {
				if (Belong[u] == Belong[v]) continue;
				++d_out[Belong[u]];
				++d_in[Belong[v]];
			}
		}
		int cnt = 0, pos = -1;
		for (int i = 1; i <= scc; ++i) {
			if (d_out[i] == 0) {
				++cnt;
				pos = i;
			}
		}
		if (cnt != 1) puts("0");
		else printf("%d\n", num[pos]);
	}
}tarjan;

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		tot = 0;
		memset(h, -1, sizeof (h[0]) * (n + 10));
		for (int i = 1, u, v; i <= m; ++i) {
			scanf("%d%d", &u, &v);
			addedge(u, v);
			addedge(v, u);
		}
		tarjan.gao(n);
		tarjan.gogogo();
	}
	return 0;
}
