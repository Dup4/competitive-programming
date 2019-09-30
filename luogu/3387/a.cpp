#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
int n, m, w[N];
vector <vector<int>> G, T;
struct Tarjan {
	//Low[i] 点i第一次访问的时间戳
	//DFN[i] 点i能访问到的点中的Low的最小值
	//Belong[i] 点i属于哪个scc
	//num[i] 第i个scc有几个点
	int Low[N], DFN[N], sta[N], Belong[N], num[N], scc; bool Insta[N];
	int d[N], f[N]; 
	void dfs(int u) {
		Low[u] = DFN[u] = ++*Low;
		sta[++*sta] = u;
		Insta[u] = 1;
		for (auto &v : G[u]) {
			if (!DFN[v]) {
				dfs(v);
				Low[u] = min(Low[u], Low[v]);
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
				num[scc] += w[v];
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
	void Topo() {
		int res = 0;
		memset(f, 0, sizeof (f[0]) * (scc + 10));
		queue <int> que;
		for (int i = 1; i <= scc; ++i) if (!d[i])
			que.push(i);
		while (!que.empty()) {
			int u = que.front(); que.pop();
			f[u] += num[u];
			res = max(res, f[u]);
			for (auto &v : T[u]) {
				f[v] = max(f[v], f[u]);
				if (--d[v] == 0) 
					que.push(v);
			}
		}
		printf("%d\n", res);
	}
	void gogogo() {
		memset(d, 0, sizeof (d[0]) * (scc + 10));
		T.clear(); T.resize(scc + 10);
		for (int u = 1; u <= n; ++u) {
			for (auto &v : G[u]) {
				if (Belong[u] == Belong[v]) continue;
				T[Belong[u]].push_back(Belong[v]);
				++d[Belong[v]];
			}
		}
		Topo();
	}
}tarjan;

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%d", w + i);
		G.clear(); G.resize(n + 1);
		for (int i = 1, u, v; i <= m; ++i) {
			scanf("%d%d", &u, &v);
			G[u].push_back(v);
		}
		tarjan.gao(n);
		tarjan.gogogo();
	}
	return 0;
}
