#include <bits/stdc++.h>
using namespace std;

#define db double
const int N = 2e5 + 10;
int n, m, in[N], out[N];
db f[N];
struct Edge {int v, nx, w;}e[N]; int h[N];
inline void addedge(int u, int v, int w) { e[++*h] = {v, h[u], w}; h[u] = *h;}
void Toposort() {
	memset(f, 0, sizeof (f[0]) * (n + 1));
	queue <int> q;
	for (int i = 1; i <= n; ++i) if (!in[i]) q.push(i), f[i] = 1; 
	db ans = 0;
	while (!q.empty()) {
		int u = q.front(); q.pop();
		if (u == n) break;
		for (int i = h[u]; i; i = e[i].nx) {
			int v = e[i].v, w = e[i].w;
			f[v] += f[u] / out[u];
			ans += 1ll * w * f[u] / out[u];
			if (--in[v] == 0) q.push(v);
		}
	}
	printf("%.2f\n", ans);
}

int main() {
	scanf("%d%d", &n, &m);
    memset(h, 0, sizeof (h[0]) * (m + 1));	
	memset(in, 0, sizeof (in[0]) * (n + 1));
	memset(out, 0, sizeof (out[0]) * (n + 1));
	for (int i = 1, u, v, w; i <= m; ++i) {
		scanf("%d%d%d", &u, &v, &w);
		addedge(u, v, w);
		++in[v]; ++out[u];
	}
	Toposort();
	return 0;
}
