#include <bits/stdc++.h>
using namespace std;

#define db double
const int N = 2e5 + 10;
int n, m, d[N], ord[N];
db f[N];
struct Edge {int v, nx, w;}e[N]; int h[N];
inline void addedge(int u, int v, int w) { e[++*h] = {v, h[u], w}; h[u] = *h;}
void Toposort() {
	*ord = 0;
	queue <int> q;
	for (int i = 1; i <= n; ++i) if (!d[i]) q.push(i);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		ord[++*ord] = u;
		if (u == n) break;
		for (int i = h[u]; i; i = e[i].nx) {
			int v = e[i].v;
			if (--d[v] == 0) q.push(v);
		}
	}
	memset(f, 0, sizeof (f[0]) * (n + 1));
	for (int _ = *ord; _ >= 1; --_) {
		int u = ord[_], G = 0; 
		for (int i = h[u]; i; i = e[i].nx) {
			++G;
			int v = e[i].v, w = e[i].w;
			f[u] += (f[v] + w);
		}
		if (!G) continue;
		f[u] = f[u] * 1.0 / G;
	}
	printf("%.2f\n", f[1]);
}

int main() {
	scanf("%d%d", &n, &m);
    memset(h, 0, sizeof (h[0]) * (m + 1));	
	memset(d, 0, sizeof (d[0]) * (n + 1));
	for (int i = 1, u, v, w; i <= m; ++i) {
		scanf("%d%d%d", &u, &v, &w);
		addedge(u, v, w);
		++d[v]; 
	}
	Toposort();
	return 0;
}
