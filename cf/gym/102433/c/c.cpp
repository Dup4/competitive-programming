#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10, INF = 1e9;
int n, m;

vector <vector<int>> G;

int dis[N], use[N];

void bfs(int st) {
	for (int i = 1; i <= n; ++i) {
		dis[i] = INF;
		use[i] = 0;
	}
	queue <int> que;
	que.push(st);
	dis[st] = 0;
	use[st] = 1;
	while (!que.empty()) {
		int u = que.front(); que.pop();
		for (auto &v : G[u]) {
			if (dis[v] > dis[u] + 1) {
				dis[v] = dis[u] + 1;
				que.push(v);
			}
		}
	}
}

int main() {
	scanf("%d%d", &n, &m);
	G.clear(); G.resize(n + 1);
	for (int i = 1, u, v; i <= m; ++i) {
		scanf("%d%d", &u, &v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	bfs(1);
	printf("%d\n", dis[n] - 1);
	return 0;
}
