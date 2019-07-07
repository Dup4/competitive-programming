#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
const ll p = 1e9 + 7;
int n, k;
ll res;
vector <vector<int>> G;

void DFS(int u, int fa) {
	int sze = 1 + (u != 1);
	for (auto v : G[u]) if (v != fa) {
		res = res * max(0, k - sze) % p;
	    ++sze;	
		DFS(v, u);	
	}
}

int main() {
	while (scanf("%d%d", &n, &k) != EOF) {
		G.clear(); G.resize(n + 1);
		for (int i = 1, u, v; i < n; ++i) {
			scanf("%d%d", &u, &v);
			G[u].push_back(v);
			G[v].push_back(u);
		}
		res = k;
		DFS(1, 1);
		printf("%lld\n", res);
	}
	return 0;
}
