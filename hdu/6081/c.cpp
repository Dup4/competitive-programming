#include <bits/stdc++.h>
using namespace std;
using pII = pair <int, int>;
#define fi first
#define se second
const int N = 3e3 + 10, M = 1e5;
const int INF = 0x3f3f3f3f;
int n, m;
struct StoerWagner {
	int val[N], fa[N], link[N];
	bool vis[N];
	struct E { int to, nx, w; }e[M * 2]; int h[N];
	void init() {
		memset(link, 0, sizeof (link[0]) * (n + 10));
		memset(fa, 0, sizeof (fa[0]) * (n + 10));
		memset(h, 0, sizeof (h[0]) * (n + 10));
	}
	void addedge(int u, int v, int w) { e[++*h] = E{v, h[u], w}; h[u] = *h; }
	int find(int u) { return fa[u] == 0 ? u : fa[u] = find(fa[u]); }
	void merge(int u, int v) {
		int p = u;
		while (link[p]) p = link[p];
		link[p] = v;
		fa[v] = u; 
	}
	int MinimumCutPhase(int &s, int &t, int cnt) {
		memset(val, 0, sizeof (val[0]) * (n + 10));
		memset(vis, 0, sizeof (vis[0]) * (n + 10));
		priority_queue <pII> pq;
		t = 1;
		while (--cnt) {
			vis[s = t] = true;
			for (int u = s; u; u = link[u]) {
				for (int i = h[u]; i; i = e[i].nx) {
					int v = find(e[i].to);
					if (!vis[v]) {
						pq.push(pII(val[v] += e[i].w, v));
					}
				}
			}
			t = 0;
			while (!t) {
				if (pq.empty()) return 0; //图不连通
				auto pa = pq.top(); pq.pop();
				if (val[pa.se] == pa.fi) {
					t = pa.se;
				}
			}
		}
		return val[t];
	}
	int gao() {
		int res = INF;
		for (int i = n, s, t; i > 1; --i) {
			res = min(res, MinimumCutPhase(s, t, i));
			if (res == 0)
				break;
			merge(s, t);
		}
		return res;
	}
}sw;

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		sw.init();
		for (int i = 1, u, v, w; i <= m; ++i) {
			scanf("%d%d%d", &u, &v, &w);
			sw.addedge(u, v, w);
			sw.addedge(v, u, w);
		}		
		printf("%d\n", sw.gao());
	}
	return 0;
}
