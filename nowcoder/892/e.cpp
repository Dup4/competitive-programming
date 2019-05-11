#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 1000010
#define INFLL 0x3f3f3f3f3f3f3f3f
int n, m, k;
struct Graph {
	struct node {
		int to, nx, w;
		node () {}
		node (int to, int nx, int w) : to(to), nx(nx), w(w) {}
	}a[N << 1];
	int head[N], pos;
	void init() {
		memset(head, 0, sizeof head);
		pos = 0;
	}
	void add(int u, int v, int w) {
		a[++pos] = node(v, head[u], w); head[u] = pos;
		a[++pos] = node(u, head[v], w); head[v] = pos;
	}
}G;
#define erp(u) for (int it = G.head[u], v = G.a[it].to, w = G.a[it].w; it; it = G.a[it].nx, v = G.a[it].to, w = G.a[it].w)

struct node {
	int to, s;
	ll w;
	node () {}
	node (int to, int s, ll w) : to(to), s(s), w(w) {}
	bool operator < (const node &other) const {
		return w > other.w; 
	}	
};

ll dis[N][10];
int used[N][10];
void Dijkstra() {
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j <= k; ++j) {
			dis[i][j] = INFLL;
			used[i][j] = 0;
		}
	}
	dis[1][0] = 0;
	priority_queue <node> pq; pq.push(node(1, 0, 0));
	while (!pq.empty()) {
		int u = pq.top().to, s = pq.top().s; pq.pop();
		if (used[u][s]) {
			continue;
		}
		used[u][s] = 1;
		erp(u) if (!used[v][s] && dis[v][s] > dis[u][s] + w) {
			dis[v][s] = dis[u][s] + w;
			pq.push(node(v, s, dis[v][s]));	
		}
		if (s < k) {
			erp(u) if (!used[v][s + 1] && dis[v][s + 1] > dis[u][s] + 1) {
				dis[v][s + 1] = dis[u][s] + 1;
				pq.push(node(v, s + 1, dis[v][s + 1]));
			}
		}
	}
}


int main() {
	while (scanf("%d%d%d", &n, &m, &k) != EOF) {
		G.init();
		for (int i = 1, u, v, w; i <= m; ++i) {
			scanf("%d%d%d", &u, &v, &w);
			G.add(u, v, w);
		}
		Dijkstra();
		ll res = INFLL;
		for (int i = 0; i <= k; ++i) {
			res = min(res, dis[n][i]);
		}
		printf("%lld\n", res);
	}
	return 0;
}
