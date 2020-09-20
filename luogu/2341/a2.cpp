#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int n, m;
vector <vector<int>> G;

struct Tarjan {
	int Low[N], DFN[N], Belong[N], num[N], sta[N], cntSCC; 
	int d_in[N], d_out[N];
	bool InSta[N];
	void dfs(int u) {
		Low[u] = DFN[u] = ++*Low;
		sta[++(*sta)] = u;
		InSta[u] = 1;
		for (auto &v : G[u]) {
			if (!DFN[v]) {
				dfs(v);
				Low[u] = min(Low[u], Low[v]);
			} else if (InSta[v]) {
				Low[u] = min(Low[u], DFN[v]);
			}
		}
		if (Low[u] == DFN[u]) {
			++cntSCC;
			int v;
			do {
				v = sta[(*sta)--];
				Belong[v] = cntSCC;
				++num[cntSCC];
				InSta[v] = 0;
			} while (v != u);
		}
	}
	int gao() {
		memset(Low, 0, sizeof Low);
		memset(DFN, 0, sizeof DFN);
		memset(InSta, 0, sizeof InSta);
		*Low = *sta = cntSCC = 0;
		for (int i = 1; i <= n; ++i) if (!DFN[i])
			dfs(i);
		memset(d_in, 0, sizeof d_in);
		memset(d_out, 0, sizeof d_out);
		for (int u = 1; u <= n; ++u) {
			for (auto &v : G[u]) {
				if (Belong[u] != Belong[v]) {
					++d_out[Belong[u]];
					++d_in[Belong[v]];
				}
			}
		}
		int zero = 0;
		for (int i = 1; i <= cntSCC; ++i)
			zero += d_out[i] == 0;
		if (zero > 1) return 0;
		return num[1];
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
