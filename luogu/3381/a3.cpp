#include <bits/stdc++.h>
using namespace std;
struct Min_Cost_Max_Flow {
	static const int N = 5e3 + 10;
	static const int M = 5e4 + 10;
	static const int INF = 0x3f3f3f3f;
	struct E { int to, nx, cap, flow, cost; }edge[M << 1]; int head[N], tot;
	int pre[N], dis[N]; 
	bool vis[N];
	int n;
	void init(int _n) {
		n = _n;
		tot = 0;
		memset(head, -1, sizeof head);
	}
	void addedge(int u, int v, int cap, int cost) {
		edge[tot] = { v, head[u], cap, 0, cost}; head[u] = tot++;
		edge[tot] = { u, head[v], 0, 0, -cost}; head[v] = tot++;
	}
	bool spfa(int s, int t) {
		queue <int> q;
		for (int i = 1; i <= n; ++i) {
			dis[i] = INF;
			vis[i] = false;
			pre[i] = -1;
		}
		dis[s] = 0;
		vis[s] = true;
		q.push(s);
		while (!q.empty()) {
			int u = q.front(); q.pop();
			vis[u] = false;
			for (int i = head[u]; i != -1; i = edge[i].nx) {
				int v = edge[i].to;
				if (edge[i].cap > edge[i].flow && dis[v] > dis[u] + edge[i].cost) {
					dis[v] = dis[u] + edge[i].cost;
					pre[v] = i;
					if (!vis[v]) {
						vis[v] = true;
						q.push(v);
					}
				}
			}
		}
		if (pre[t] == -1) return false;
		return true;
	}
	int gao(int s, int t, int &cost) {
		int flow = 0;
		cost = 0;
		while (spfa(s, t)) {
			int Min = INF;
			for (int i = pre[t]; i != -1; i = pre[edge[i ^ 1].to]) {
				if (Min > edge[i].cap - edge[i].flow) {
					Min = edge[i].cap - edge[i].flow;
				}
			}
			for (int i = pre[t]; i != -1; i = pre[edge[i ^ 1].to]) {
				edge[i].flow += Min;
				edge[i ^ 1].flow -= Min;
				cost += edge[i].cost * Min;
			}
			flow += Min;
		}
		return flow;
	}
}MCMF;

int n, m, s, t;
int flow, cost;

int main() {
	while (scanf("%d%d%d%d", &n, &m, &s, &t) != EOF) {
		MCMF.init(n);
		for (int i = 1, u, v, w, f; i <= m; ++i) {
			scanf("%d%d%d%d", &u, &v, &w, &f);
			MCMF.addedge(u, v, w, f);
		}
		flow = MCMF.gao(s, t, cost);
		printf("%d %d\n", flow, cost);
	}
    return 0;
}
