#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10, INF = 0x3f3f3f3f;
int n, m, s;

struct Graph {
	struct E { int to, nx, w; }e[N << 1]; int h[N], cnt;
	void init(int n) { for (int i = 0; i <= n; ++i) h[i] = -1; cnt = -1; }
	void addedge(int u, int v, int w = 0) { e[++cnt] = { v, h[u], w}; h[u] = cnt; } 
}G;

struct Dijkstra {
	struct node {
		int u, w;
		node(int u = 0, int w = 0) : u(u), w(w) {}
		bool operator < (const node &other) const { return w > other.w; }		
	};
	int dis[N]; bool used[N];
	void gao(int s) {
		for (int i = 1; i <= n; ++i) {
			dis[i] = INF;
			used[i] = 0;
		}
		priority_queue <node> pq;
		dis[s] = 0;
		pq.push(node(s, dis[s]));
		while (!pq.empty()) {
			int u = pq.top().u; pq.pop();
			if (used[u]) continue;
			used[u] = 1;
			for (int i = G.h[u]; ~i; i = G.e[i].nx) {
				int v = G.e[i].to, w = G.e[i].w;
				if (dis[v] > dis[u] + w) {
					dis[v] = dis[u] + w;
					pq.push(node(v, dis[v]));
				}
			}
		}
	}
}dij;

int main() {
	scanf("%d%d%d", &n, &m, &s);
	G.init(n);
	for (int i = 1, u, v, w; i <= m; ++i) {
		scanf("%d%d%d", &u, &v, &w);
		G.addedge(u, v, w);
	}
	dij.gao(s);
	for (int i = 1; i <= n; ++i)
		printf("%d%c", dij.dis[i],  " \n"[i == n]);
	return 0;
}
