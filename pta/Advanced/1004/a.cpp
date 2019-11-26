#include <bits/stdc++.h>
using namespace std;
const int N = 1e4 + 10;
int n, m, Max, ans[N];
vector <vector<int>> G;
void dfs(int u, int dep) {
	Max = max(Max, dep);
	if (G[u].size() == 0) {
		++ans[dep];
	}	
	for (auto &v : G[u]) {
		dfs(v, dep + 1); 
	}
}

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		memset(ans, 0, sizeof ans);
		G.clear(); G.resize(n + 10);
		Max = 0;
		for (int i = 1, sze, u; i <= m; ++i) {
			scanf("%d%d", &u, &sze);
			for (int j = 1, v; j <= sze; ++j) {
				scanf("%d", &v);
				G[u].push_back(v);
			}
		}
		dfs(1, 0);
		for (int i = 0; i <= Max; ++i) {
			printf("%d%c", ans[i], " \n"[i == Max]);
		}
	}
	return 0;
}
