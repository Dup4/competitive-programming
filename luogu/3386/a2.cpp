#include <bits/stdc++.h>
using namespace std;

const int N = 1e3 + 10; 
const int INF = 0x3f3f3f3f;
int n, m, e;
vector <vector<int>> G;
struct Hungary {
	//uN　左边的点数
	//linker[i] 右边的第i个点连向左边的点
	int uN, linker[N]; bool used[N];
	bool dfs(int u) {
		for (auto &v : G[u]) {
			if (!used[v]) {
				used[v] = true;
				if (linker[v] == -1 || dfs(linker[v])) {
					linker[v] = u;
					return true;
				}
			}
		}
		return false;
	}
	int gao() {
		int res = 0;
		memset(linker, -1, sizeof linker);
		for (int u = 0; u < uN; ++u) {
			memset(used, 0, sizeof used);
			if (dfs(u)) ++res;
		}
		return res;
	}
}hungary;

int main() {
	while (scanf("%d%d%d", &n, &m, &e) != EOF) { 
		hungary.uN = n;
		G.clear(); G.resize(n + 1);
		for (int i = 1, u, v; i <= e; ++i) {
			scanf("%d%d", &u, &v);
			--u, --v;
			if (u >= n || v >= m) continue;
			G[u].push_back(v);
		}
		printf("%d\n", hungary.gao());
	}
	return 0;
}

