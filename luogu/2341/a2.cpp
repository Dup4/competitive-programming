#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int n, m;
vector <vector<int>> G;

struct Tarjan {
	int DFN[N], Low[N], Sta[N], InSta[N], Belong[N], num[N], cntSCC, In[N], Out[N];
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
			++cntSCC;
			int v;
			do {
				v = Sta[(*Sta)--];
				InSta[v] = 0;
				Belong[v] = cntSCC;
				++num[cntSCC];	
			} while (u != v);
		}
	}
	int gao() {
		cntSCC = 0;
		*DFN = 0;
		*Sta = 0;
		memset(DFN, 0, sizeof DFN);
		memset(In, 0, sizeof In);
		memset(Out, 0, sizeof Out);
		memset(num, 0, sizeof num);
		for (int i = 1; i <= n; ++i) if (!DFN[i])
			dfs(i);
		for (int u = 1; u <= n; ++u) {
			for (auto &v : G[u]) {
				if (Belong[u] != Belong[v]) {
					++Out[Belong[u]];
					++In[Belong[v]];
				}
			}
		}
		int cnt = 0, _num = 0;
		for (int i = 1; i <= cntSCC; ++i) {
			if (Out[i] == 0) {
				++cnt;
				_num = num[i];
			}
		}
		if (cnt > 1) return 0;
		return _num;
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
