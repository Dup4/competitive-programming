#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
int n, K;
vector <vector<int>> G;

int fa[N], md[N], hson[N], deep[N], use[N];

void dfs(int u) {
	hson[u] = 0;
	for (auto &v : G[u]) {
		deep[v] = deep[u] + 1;
		dfs(v);
		if (!hson[u] || md[v] > md[hson[u]]) hson[u] = v;
	}
	md[u] = md[hson[u]] + 1;
}

int main() {
	scanf("%d%d", &n, &K);
	G.resize(n + 1);
	fa[1] = 1;
	deep[1] = 0;
	for (int i = 2; i <= n; ++i) {
		scanf("%d", fa + i);
		G[fa[i]].push_back(i);
	}
	int cnt = 0;
	for (int i = 2; i<= n; ++i) if (G[i].empty()) {
		++cnt;
	}
	if (K >= cnt) {
		printf("%d\n", n);
	} else {
		dfs(1);
		vector <int> vec;
		for (int i = 1; i <= n; ++i) if (hson[i]) use[hson[i]] = 1;
		for (int i = 1; i <= n; ++i) if (use[i] == 0) {
			vec.push_back(md[i]);
		}
		sort(vec.begin(), vec.end(), [&](int x, int y) { return x > y; });
		int sum = 0;
		for (int i = 0; i < K; ++i) sum += vec[i];
		printf("%d\n", sum);
	}
	return 0;
}
