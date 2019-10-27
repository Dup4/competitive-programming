#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10, INF = 0x3f3f3f3f;
int n, m, S, dis[N];
vector <vector<int>> G;

void bfs() {
	queue <int> q;
	for (int i = 1; i <= n; ++i) dis[i] = INF;
	dis[S] = 0;
	set <int> A, B;
	for (int i = 1; i <= n; ++i) A.insert(i);
	A.erase(S);
	q.push(S);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		B.clear();
		for (auto &v : G[u]) {
			if (!A.count(v)) continue;
			B.insert(v);
			A.erase(v);
		}
		for (auto &v : A) {
			dis[v] = dis[u] + 1;
			q.push(v);
		}
		A = B;
	}
	vector <int> res;
	for (int i = 1; i <= n; ++i) {
		if (i == S) continue;
		if (dis[i] == INF) dis[i] = -1;
		res.push_back(dis[i]);
	}
	for (int i = 0; i < n - 1; ++i) 
		printf("%d%c", res[i], " \n"[i == n - 2]);
}

int main() {
	int _T; scanf("%d", &_T);
	while (_T--) {
		scanf("%d%d", &n, &m);
		G.clear(); G.resize(n + 1);
		for (int i = 1, u, v; i <= m; ++i) {
			scanf("%d%d", &u, &v);
			G[u].push_back(v);
			G[v].push_back(u);
		}
		scanf("%d", &S);
		bfs();
	}
	return 0;
}
