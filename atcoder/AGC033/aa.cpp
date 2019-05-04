#include <bits/stdc++.h>
using namespace std;

#define N 1010
#define M 1000010
#define INF 0x3f3f3f3f
int n, m;
char s[N]; 
int dist[M], used[M];
vector < vector <int> > G;
int id(int x, int y) {
	return (x - 1) * m + y;
}
int Move[][2] = {
	{-1, 0},
	{1, 0},
	{0, 1},
	{0, -1},
};
bool ok(int x, int y) {
	if (x < 1 || x > n || y < 1 || y > m) {
		return false;
	}
	return true;
}
struct node {
	int u, w;
	node () {}
	node (int u, int w) : u(u), w(w) {}
	bool operator < (const node &other) const {
		return w > other.w;
	}
};
void Dijkstra() {
	priority_queue <node> pq;
	pq.push(node(0, -1));
	while (!pq.empty()) {
		int u = pq.top().u; pq.pop();
		if (used[u]) {
			continue;
		}
		used[u] = 1;
		for (auto v : G[u]) {
			if (!used[v] && dist[v] > dist[u] + 1) {
				dist[v] = dist[u] + 1;
				pq.push(node(v, dist[v]));
			}
		}
	}
}

void init() {
	G.clear();
	G.resize(n * m + 1);
	for (int i = 1; i <= n * m; ++i) {
		dist[i] = INF;
		used[i] = 0;
	}
	used[0] = 0;
	dist[0] = -1;
}
int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		init();
		for (int i = 1; i <= n; ++i) {
			scanf("%s", s + 1);
			for (int j = 1; j <= m; ++j) {
				if (s[j] == '#') {
					G[0].push_back(id(i, j)); 
				}
				for (int k = 0; k < 4; ++k) {
					int x = i + Move[k][0];
					int y = j + Move[k][1];
					if (ok(x, y)) {
						G[id(i, j)].push_back(id(x, y));
						G[id(x, y)].push_back(id(i, j));
					}
				}
			}
		}
		Dijkstra();
		int res = 0;
		for (int i = 1; i <= n * m; ++i) {
			res = max(res, dist[i]);
		}
		printf("%d\n", res);
	}
	return 0;
}
