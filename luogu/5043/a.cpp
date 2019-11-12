#include <bits/stdc++.h>
using namespace std;
using uint = unsigned int;
const int N = 1e2 + 10;
int n, m;

struct Hash {
	vector <vector<int>> G;
	uint a[N], base = 233;
	int n;
	uint dfs(int u, int fa) {
		vector <uint> vec;
		for (auto &v : G[u]) if (v != fa) {
			vec.push_back(dfs(v, u));	
		}
		sort(vec.begin(), vec.end());
		uint now = 1;
		for (auto &it : vec) {
			now = now * base + it;
		}
		return now * base + 1;
	}
	void init(int _n) { n = _n; G.clear(); G.resize(n + 1); }
	void add(int u, int v) {
		G[u].push_back(v);
		G[v].push_back(u);
	}
	void gao() {
		for (int i = 1; i <= n; ++i) {
			a[i] = dfs(i, 0);
		}
		sort(a + 1, a + 1 + n);
	}
}hs[N];

bool same(const Hash &x, const Hash &y) {
	if (x.n != y.n) return false;
	for (int i = 1; i <= n; ++i) {
		if (x.a[i] != y.a[i])
			return false;
	}
	return true;
}

int main() {
	while (scanf("%d", &m) != EOF) {
		for (int i = 1; i <= m; ++i) {
			scanf("%d", &n);
			hs[i].init(n);
			for (int j = 1, x; j <= n; ++j) {
				scanf("%d", &x);
				if (x) hs[i].add(x, j);
			}
			hs[i].gao();
			for (int j = 1; j <= i; ++j) {
				if (same(hs[j], hs[i])) {
					printf("%d\n", j);
					break;
				}
			}				
		}
	}
	return 0;
}
