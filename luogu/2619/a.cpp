#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e5 + 10;
const ll INF = 0x3f3f3f3f3f3f3f3f; 
struct Edge { 
	int u, v, w, k, vis; 
	Edge() {}
	Edge(int u, int v, int w, int vis) : u(u), v(v), w(w), vis(vis) {k = 0;}
	bool operator < (const Edge &other) const {
		if (k + w == other.k + other.w) return vis > other.vis;
		return k + w < other.k + other.w;
	}
}e[N];
int fa[N]; 
int find(int x) { return !fa[x] ? x : fa[x] = find(fa[x]); }
inline void merge(int u, int v) {
	u = find(u), v = find(v);
	fa[u] = v; 
}
int n, m, C; 
int check(int K) {
	for (int i = 1; i <= m; ++i) {
		e[i].k = e[i].vis * K; 
	}
	sort(e + 1, e + 1 + m);
	memset(fa, 0, sizeof fa);
	int cnt_e = 0; ll tot = 0; 
	for (int i = 1; i <= m; ++i) {
		int u = e[i].u, v = e[i].v, w = e[i].w;
		if (find(u) == find(v)) continue;
		cnt_e += e[i].vis; 
		merge(u, v);
		tot += w;
	} 
	return cnt_e;
}

int calc(int K) {
	for (int i = 1; i <= m; ++i) {
		e[i].k = e[i].vis * K;
	}
	sort(e + 1, e + 1 + m);
	memset(fa, 0, sizeof fa);
	int cnt_e = 0; ll tot = 0; 
	for (int i = 1; i <= m; ++i) {
		int u = e[i].u, v = e[i].v, w = e[i].w;
		if (find(u) == find(v) || (e[i].vis && cnt_e >= C)) continue;
		cnt_e += e[i].vis;
		merge(u, v);
		tot += w;
	}
	assert(cnt_e == C);
	return tot;
}

int main() {
	while (scanf("%d%d%d", &n, &m, &C) != EOF) {
		for (int i = 1, u, v, w, vis; i <= m; ++i) {
			scanf("%d%d%d%d", &u, &v, &w, &vis);
			++u, ++v;
			e[i] = Edge(u, v, w, vis ^ 1);
		}
		int l = -200, r = 100;
		while (l < r) { 
			int mid = (l + r + 1) >> 1;
			if (check(mid) < C) { 
				r = mid - 1;
			} else {
				l = mid;
			}
		}
		printf("%d\n", calc(l));
	}
	return 0;
}
