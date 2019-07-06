#include <bits/stdc++.h>
using namespace std;

#define N 1100
#define pii pair <int, int>
#define fi first
#define se second
int n, leaf[N];
vector <vector<pii>> G;
struct node {
	int u, v, w;
	node() {}
	node(int u, int v, int w) : u(u), v(v), w(w) {}
};
vector <node> res;

bool ok() {
	for (int i = 1; i <= n; ++i) {
		if (G[i].size() == 2) {
			return 0;
		}
	}	
	return 1;
}

int getleaf(int u, int fa) {
	if (G[u].size() == 1) return u;
	for (auto v : G[u]) if (v != fa) {
		return getleaf(v); 
	}
}

void DFS(int u, int fa) {
	for (int i = 0, sze = (int)G[u].size(); i < sze; ++i) {
		if (G[u][i] == fa) {
			G[u].erase(i);
			break;
		}
	}
	
}
	
int main() {
	while (scanf("%d", &n) != EOF) {
		G.clear(); G.resize(n + 1);
		for (int i = 1, u, v, w; i < n; ++i) {
			scanf("%d%d%d", &u, &v, &w);
			G[u].push_back(v, w);
			G[v].push_back(u, w);
		}
		if (!ok()) {
			puts("NO");
		} else {
			res.clear();
			DFS(1, 1);
			puts("YES");
			for (auto it : res) {
				printf("%d %d %d\n", it.u, it.v, it.w);
			}
		}
	}
	return 0;
}
