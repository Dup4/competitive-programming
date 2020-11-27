#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int n, m;
vector <vector<int>> G;

struct Tarjan {
	int DFN[N], Low[N], Sta[N], InSta[N], Belong[N], num[N], cntSCC;
	int Out[N];
	void dfs(int u) {
		DFN[u] = Low[u] = ++*DFN;
		Sta[++*Sta] = u;
		InSta[u] = 1;
		for (auto &v : G[u]) {
			if (!DFN[v]) {
				dfs(v);
				Low[u] = min(Low[u], Low[v]);
			} else {
				Low[u] = min(Low[u], DFN[v]);
			}
		}
		if (Low[u] == DFN[u]) {
			int v;
			++cntSCC;
			do {
				v = Sta[(*Sta)--];
				Belong[v] = cntSCC;
				++num[cntSCC];
				InSta[v] = 0;
			} while (u != v);
		}
	}
	int gao() {
		*DFN = *Sta = cntSCC = 0;
		memset(DFN, 0, sizeof DFN);
		memset(InSta, 0, sizeof InSta);
		memset(num, 0, sizeof num);
		memset(Out, 0, sizeof Out);
		for (int i = 1; i <= n; ++i) if (!DFN[i])
			dfs(i);
		for (int u = 1; u <= n; ++u) {
			for (auto &v : G[u]) {
				if (Belong[u] != Belong[v]) {
					++Out[Belong[u]];
				}
			}
		}
		int cnt = 0, Max = 0;
		for (int i = 1; i <= cntSCC; ++i) {
			if (Out[i] == 0) {
				++cnt;
				Max = num[i];
			}
		}
		if (cnt > 1) return 0;
		return Max;
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
