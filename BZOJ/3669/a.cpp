#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e5 + 10;
const int INF = 0x3f3f3f3f;
int n, m, cnt; 
struct Edge {
	int u, v, a, b;
	bool operator < (const Edge &other) const {
		return a < other.a;
	}
}e[N];
vector < vector<Edge> > G;
int dis[N];
queue <int> q;
void spfa() {
	if (q.empty()) return;
	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (int i = 0, sze = G[u].size(); i < sze; ++i) {
			int v = G[u][i].v, w = G[u][i].b;
			if (max(dis[u], w) < dis[v]) {
				dis[v] = max(dis[u], w);
				q.push(v);
			}
		}
	}
}

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		G.clear(); G.resize(n + 1); cnt = 0;
		memset(dis, 0x3f, sizeof dis); dis[1] = 0;
		for (int i = 1, u, v, a, b; i <= m; ++i) {
			scanf("%d%d%d%d", &u, &v, &a, &b);
			if (u == v) continue;
			e[++cnt] = {u, v, a, b};
		}
		m = cnt;
		sort(e + 1, e + 1 + m);
		int res = INF;
		for (int i = 1; i <= m; ++i) {
			int u = e[i].u, v = e[i].v, w = e[i].b;
			G[u].push_back(e[i]);
			swap(e[i].u, e[i].v);
			G[v].push_back(e[i]); 
			if (max(dis[u], w) < dis[v]) {
				dis[v] = max(dis[u], w);
				q.push(v);
			}
			if (max(dis[v], w) < dis[u]) {
				dis[u] = max(dis[v], w);
				q.push(u);
			}
			spfa();
			res = min(res, e[i].a + dis[n]);
		}
		if (res == INF) res = -1;
		printf("%d\n", res);
	}
	return 0;
}
