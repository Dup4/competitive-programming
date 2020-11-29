#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int n, m;
vector <vector<int>> G;

struct Tarjan {
	int DFN[N], Low[N], Sta[N], InSta[N], Belong[N], num[N], Out[N];
	int cntSCC;
	void dfs(int u) {
		DFN[u] = Low[u] = ++*Low;
		InSta[u] = 1;
		Sta[++*Sta] = u;
		for (auto &v : G[u]) {
			if (!DFN[v]) {
				dfs(v);
				Low[u] = min(Low[u], Low[v]);
			} else if (InSta[v]) {
				Low[u] = min(Low[u], DFN[v]);
			}
		}
		if (DFN[u] == Low[u]) {
			++cntSCC;
			int v;
			do {
				v = Sta[(*Sta)--];
				InSta[v] = 0;
				Belong[v] = cntSCC;
				++num[cntSCC];
			} while (v != u);
		}
	}
	int gao() {
		memset(DFN, 0, sizeof DFN);
		memset(Low, 0, sizeof Low);
		memset(InSta, 0, sizeof InSta);
		memset(Out, 0, sizeof Out);
		cntSCC = *Sta = *Low = 0;
		for (int i = 1; i <= n; ++i) {
			if (!DFN[i]) {
				dfs(i);
			}
		}
		for (int u = 1; u <= n; ++u) {
			for (auto &v : G[u]) {
				if (Belong[u] != Belong[v]) {
					++Out[Belong[u]];
				}
			}
		}	
		int cnt = 0, res = 0;
		for (int i = 1; i <= cntSCC; ++i) {
			if (Out[i] == 0) {
				++cnt;
				res = num[i];
			}
		}
		if (cnt != 1) return 0;
		return res;
	}
}tarjan;



int main() {
	scanf("%d%d", &n, &m);
	G.clear(); G.resize(n + 1);
	for (int i = 1, u, v; i <= m; ++i) {
		scanf("%d%d", &u, &v);
		G[u].push_back(v);
	}
	printf("%d\n", tarjan.gao());
	return 0;
}
