#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;

int n, m;
int dep[N], sze[N], a[N], vis[N];
vector<vector<int> >G;

void gao() {
	queue<int> q;
	for (int i = 1; i <= m; ++i) q.push(a[i]);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (auto &v : G[u]) {
			if (dep[v] == 0 || dep[v] == dep[u] + 1) {
				dep[v] = dep[u] + 1;
				sze[v] += sze[u];
				if (sze[v] == m) {
					printf("YES\n%d\n", v);
					return ;
				}
				if (!vis[v]) {
					q.push(v);
					vis[v] = 1;
				}
			}
		}
	}
	puts("NO");
}

int main() {
	while (scanf("%d %d", &n, &m) != EOF) {
		G.clear();
		G.resize(n + 1);
		memset(dep, 0, sizeof dep);
		memset(sze, 0, sizeof sze);
		memset(vis, 0, sizeof vis);
		for (int i = 1, u, v; i < n; ++i) {
			scanf("%d %d", &u, &v);
			G[u].push_back(v);
			G[v].push_back(u);
		}
		for (int i = 1; i <= m; ++i) {
			scanf("%d", a + i);
			dep[a[i]] = 1;
			sze[a[i]] = 1;
			vis[a[i]] = 1;
		}
		if (n == 1) {
			puts("YES\n1");
		} else {
			gao();
		}
	}
	return 0;
}
