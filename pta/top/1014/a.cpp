#include <bits/stdc++.h>
using namespace std;

const int N = 1e3 + 10, INF = 0x3f3f3f3f;
int n, use[N];

vector <vector<int>> G;

struct BFS {
	int dis[N];
	void gao(int s) {
		memset(dis, 0x3f, sizeof dis);
		dis[s] = 0;
		queue <int> que;
		que.push(s);
		while (!que.empty()) {
			int u = que.front(); que.pop();
			use[u] = 1;
			for (auto &v : G[u]) {
				if (dis[v] > dis[u] + 1) {
					dis[v] = dis[u] + 1;
					que.push(v);
				}
			}
		}	
	}
}bfs[N];

int main() {
	scanf("%d", &n);
	G.clear(); G.resize(n + 1);
	for (int i = 1; i <= n; ++i) {
		int sze; scanf("%d", &sze);
		for (int j = 1, x; j <= sze; ++j) {
			scanf("%d", &x);
			G[i].push_back(x);
			G[x].push_back(i);
		}
	}
	memset(use, 0, sizeof use);
	int cnt = 0;
	int Max = 1;
	for (int i = 1; i <= n; ++i) {
		if (!use[i]) {
			++cnt;
		}
		bfs[i].gao(i);
		for (int j = 1; j <= n; ++j) if (bfs[i].dis[j] != INF) {
			Max = max(Max, bfs[i].dis[j]);
		}
	}
	printf("%d %d\n", cnt, Max - 1);
	return 0;
}
