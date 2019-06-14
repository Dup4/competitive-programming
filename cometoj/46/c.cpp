#include <bits/stdc++.h>
using namespace std;

#define N 500010 
int n, a[N], deep[N], fa[N], y[N];
vector < vector <int> > G, S;

void DFS(int u) {
	S[deep[u]].push_back(u);
	for (auto v : G[u]) if (v != fa[u]) {
		fa[v] = u;
		deep[v] = deep[u] + 1;
		DFS(v);
	}
}

void Toposort() {
	priority_queue <int, vector <int>, greater <int> > pq;
	int now = 1;
	while (now <= n && y[now] == 0) {
		for (auto it : S[now]) {
			pq.push(it);
		}
		++now;
	}
	vector <int> res;
	while (!pq.empty()) {
		int u = pq.top(); pq.pop();
		res.push_back(u);
		--y[a[u] + 1];
		while (now <= n && y[now] == 0) {
			for (auto it : S[now]) {
				pq.push(it);
			}
			++now;
		}
	}
	for (int i = 0; i < n; ++i) {
		printf("%d%c", res[i], " \n"[i == n - 1]);
	}
}

int main() {
	while (scanf("%d", &n) != EOF) {
		G.clear(); S.clear();
		G.resize(n + 1); S.resize(n + 1);
		memset(y, 0, sizeof y);
		for (int i = 1, u, v; i < n; ++i) {
			scanf("%d%d", &u, &v);
			G[u].push_back(v);
			G[v].push_back(u);
		}
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			++y[a[i] + 1]; 
		}
		deep[1] = 1; DFS(1);
		Toposort();
	}
	return 0;
}
