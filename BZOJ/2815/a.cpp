#include <bits/stdc++.h>
using namespace std;

#define N 200010
#define M 21
struct Graph {
	struct node {
		int to, nx;
		node() {}
		node(int to, int nx) : to(to), nx(nx) {} 
	}a[N * 10];
	int head[N], pos;
	void init() {
		memset(head, -1, sizeof head);
		pos = 0;
	}
	void add(int u, int v) {
		a[pos] = node(v, head[u]); head[u] = pos++; 
	}
}G[3];
#define erp(G, u) for (int it = G.head[u], v = G.a[it].to; ~it; it = G.a[it].nx, v = G.a[it].to)

int n;
int f[N][M], deep[N], d[N], sze[N];
struct Dominator_Tree {
	int que[N], l, r;
	void add(int fa, int x) {
		if (fa != x) G[2].add(fa, x);
		f[x][0] = fa; deep[x] = deep[fa] + 1;
		for (int i = 1; i < 20; ++i)
			f[x][i] = f[f[x][i - 1]][i - 1];
	}
	int querylca(int u, int v) {
		if (!u) return v;
		if (!v) return u;
		if (deep[u] > deep[v]) swap(u, v);
		for (int det = deep[v] - deep[u], i = 0; det; det >>= 1, ++i) {
			if (det & 1) {
				v = f[v][i];		
			}
		}
		if (u == v) return u;
		for (int i = M - 1; i >= 0; --i) {
			if (f[u][i] == f[v][i])
				continue;
			u = f[u][i];
			v = f[v][i];
		}
		return f[u][0];
	}
    int getlca(int x) {
		int lca = 0;
		erp(G[1], x) {
			lca = querylca(lca, v);
		}
		return lca; 
	}	
	void DFS(int u) {
		sze[u] = 1;
		erp(G[2], u) {
			if (sze[v]) continue;
			DFS(v);
			sze[u] += sze[v];
		}
	}
	void work() {
		int S = n + 1; add(S, S);
		l = 1, r = 0;
		for (int i = 1; i <= n; ++i) if (d[i] == 0) {
			que[++r] = i;
			add(S, i);
		}
		while (l <= r) {
			int u = que[l]; ++l;
			erp(G[0], u) {
				--d[v]; 
				if (d[v] == 0) {
					que[++r] = v;
					add(getlca(v), v);
				}
			}
		}
		DFS(S);
	}
}dt;

void init() {
	for (int i = 0; i < 3; ++i)
		G[i].init();
	for (int i = 0; i <= n + 1; ++i)
		deep[i] = 0, f[i][0] = 0, d[i] = 0, sze[i] = 0;
}
int main() {
	while (scanf("%d", &n) != EOF) {
		init();
		for (int i = 1, x; i <= n; ++i) {
			for (scanf("%d", &x); x; scanf("%d", &x)) {
				G[0].add(x, i);
				G[1].add(i, x);
				++d[i];
			}
		}
		dt.work();
		for (int i = 1; i <= n; ++i) 
			printf("%d\n", sze[i] - 1);
	}
	return 0;
}
