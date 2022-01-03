#include <bits/stdc++.h>
using namespace std;

#define INF 0x3f3f3f3f
#define N 510
#define M 1000010

struct Edge {
	int to, flow, nxt;
	Edge() {}
	Edge(int to, int nxt, int flow) : to(to), nxt(nxt), flow(flow) {}
}edge[M << 2];

int head[N << 2], tot, dep[N << 2];
int S, T, n, m, k;
void init() {
	memset(head, -1, sizeof head);
	tot = 0 ;	
}

void add(int u, int v, int w, int rw = 0) {
	edge[tot] = Edge(v, head[u], w); head[u] = tot++;
	edge[tot] = Edge(u, head[v], rw); head[v] = tot++; 
}

bool BFS() {
	memset(dep, -1, sizeof dep);
	queue <int> q;
	q.push(S);
	dep[S] = 1;
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (int i = head[u]; ~i; i = edge[i].nxt) {
			if (edge[i].flow && dep[edge[i].to] == -1) {
				dep[edge[i].to] = dep[u] + 1;
				q.push(edge[i].to);
			}
		}
	}
	return dep[T] >= 0;
}

int DFS(int u, int f) {
	if (u == T || f == 0) return f;
	int w, used = 0;
	for (int i = head[u]; ~i; i = edge[i].nxt) {
		if (edge[i].flow && dep[edge[i].to] == dep[u] + 1) {
			w = DFS(edge[i].to, min(f - used, edge[i].flow));
			edge[i].flow -= w;
			edge[i ^ 1].flow += w;
			used += w;
			if (used == f) return f;
		}
	}
	if (!used) dep[u] = -1;
	return used;
}

int Dicnic() {
	int ans = 0;
	while (BFS()) {
		ans += DFS(S, INF);
	}
	return ans;
}

int main() {
	while (scanf("%d%d%d", &n, &m, &k) != EOF) {
		init(); S = 0; T = n + m + 1; int C = n + m + 2;
		add(S, C, k);
		for (int i = 1; i <= n; ++i) {
			add(S, i, 1);
			add(C, i, 1);
		}
		for (int i = 1, sze, x; i <= n; ++i) {
			scanf("%d", &sze);
			while (sze--) {
				scanf("%d", &x);
				add(i, x + n, 1);
			}
		}
		for (int i = 1; i <= m; ++i) add(i + n, T, 1);
		printf("%d\n", Dicnic());
	}
	return 0;
}
