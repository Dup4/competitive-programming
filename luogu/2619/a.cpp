#include <bits/stdc++.h>
using namespace std;

typedef double db;
typedef long long ll;
const int N = 1e5 + 10;
const ll INF = 0x3f3f3f3f3f3f3f3f; 
const db eps = 1e-8;
struct Edge { 
	int u, v, w, vis; db k; 
	Edge() {}
	Edge(int u, int v, int w, int vis) : u(u), v(v), w(w), vis(vis) {k = 0;}
	bool operator < (const Edge &other) const {
		if (vis == other.vis) return w < other.w;
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
int check(db K) {
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

int calc(db K) {
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
	return tot;
}

int main() {
	while (scanf("%d%d%d", &n, &m, &C) != EOF) {
		for (int i = 1, u, v, w, vis; i <= m; ++i) {
			scanf("%d%d%d%d", &u, &v, &w, &vis);
			++u, ++v;
			e[i] = Edge(u, v, w, vis ^ 1);
		}
		db l = -2000, r = 2000, res = -2000;
		while (fabs(r - l) > eps) {
			db mid = (l + r) / 2;
			if (check(mid) <= C) {
				res = mid;
				r = mid;
			} else {
				l = mid;
			}
		}
		printf("%d\n", calc(res));
	}
	return 0;
}
