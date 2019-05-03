#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 200010
int n;
struct Graph {
	struct node {
		int to, nx, w;
		node () {}
		node (int to, int nx, int w) : to(to), nx(nx), w(w) {}
	}a[N << 1];
	int head[N], pos;
	void init(int n) {
		pos = 0;
		for (int i = 1; i <= n; ++i) {
			head[i] = -1;
		}
	} 
	void add(int u, int v, int w) {
		a[pos] = node(v, head[u], w); head[u] = pos++;
	    a[pos] = node(u, head[v], w); head[v] = pos++;	
	}
}G;
#define erp(u) for (int it = G.head[u], v = G.a[it].to, w = G.a[it].w; ~it; it = G.a[it].nx, v = G.a[it].to, w = G.a[it].w)

int root, sum, f[N], sze[N];
void getroot(int u, int fa) {
	sze[u] = 1; f[u] = 0;
	erp(u) if (v != fa) {
		getroot(v, u);
		sze[u] += sze[v];
		f[u] = max(f[u], sze[v]);
	}
	f[u] = max(f[u], sum - sze[u]);
	if (f[u] < f[root]) {
		root = u;
	}
}

ll calc(int u) {
		
}

void init() {
	G.init(n);
}
int main() {
	while (scanf("%d", &n) != EOF) {
		init();
		for (int i = 1, u, v, w; i < n; ++i) {
			scanf("%d%d%d", &u, &v, &w);
			G.add(u, v, w);
		}
		
	}
	return 0;
}
