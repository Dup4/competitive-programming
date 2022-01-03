#include <bits/stdc++.h>
using namespace std;

#define pii pair <int, int>
#define fi first
#define se second
const int N = 1e3 + 10;
int n, m, res, dis[N], used[N];
vector <vector<pii>> G;
struct node {
	int v, w;
	node() {}
	node(int v, int w) : v(v), w(w) {}
	bool operator < (const node &other) const {
		return w > other.w;
	}
};
void Dijkstra(int s) {
	memset(dis, 0, sizeof dis);
	dis[s] = 0;
	priority_queue <node> pq;
	pq.push(node(s, 0));
	while (!pq.empty()) {
		int u = pq.top().v; pq.pop();
		res = min(res, dis[u]);
		for (auto &it : G[u]) {
			int v = it.fi, w = it.se;
			if (dis[v] > dis[u] + w) {
				dis[v] = dis[u] + w;
				pq.push(node(v, dis[v]));
			}
		}
	}
}
int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		G.clear(); G.resize(n + 1);
		for (int i = 1, u, v, w; i <= m; ++i) {
			scanf("%d%d%d", &u, &v, &w);
			G[u].emplace_back(v, -w);
		}
		res = 0;
		for (int i = 1; i <= n; ++i) Dijkstra(i);
		printf("%d\n", -res);
	}
	return 0;
}
