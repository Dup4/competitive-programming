#include <bits/stdc++.h>
using namespace std;
using pII = pair<int, int>;
#define fi first
#define se second
const int N = 500 * 500 + 10;
int n, m;

struct UFS {
	int fa[N], rk[N];
	void init(int n) {
		memset(fa, 0, sizeof (fa[0]) * (n + 5));
		memset(rk, 0, sizeof (rk[0]) * (n + 5));
	}
	int find(int x) { return fa[x] == 0 ? x : fa[x] = find(fa[x]); }
	bool merge(int x, int y) {
		int fx = find(x), fy = find(y);
		if (fx != fy) {
			if (rk[fx] > rk[fy]) swap(fx, fy);
			fa[fx] = fy;
			if (rk[fx] == rk[fy]) ++rk[fy];
			return true;
		}
		return false;
	}
	bool same(int x, int y) { return find(x) == find(y); }
}ufs;

struct E {
	int u, v, w, use;
	bool operator < (const E &other) const {
		return w < other.w;
	}
}e[N];

void Kruskal() {
	sort(e + 1, e + 1 + m);
	int tot = 0;
	ufs.init(n);
	for (int i = 1; i <= m; ++i) {
		int u = e[i].u, v = e[i].v, w = e[i].w;
		if (ufs.merge(u, v)) {
			e[i].use = 1;
			tot += w;
		}
	}
	int cnt = 0;
	for (int i = 1; i <= n; ++i) {
		if (ufs.fa[i] == 0) {
			++cnt;
		}
	}
	if (cnt > 1) {
		printf("No MST\n%d\n", cnt);
		return;
	}
	ufs.init(n);
	int unique = 1;
	for (int i = 1; i <= m; ++i) {
		int j = i;
		for (; j <= m; ++j) {
			if (e[j].w > e[i].w)
				break;
		}
		--j;
		for (int k = i; k <= j; ++k) if (e[k].use == 0) {
			int u = e[k].u, v = e[k].v;
			if (!ufs.same(u, v)) {
				unique = 0;
				break;
			}
		}
		if (!unique) break;
		for (int k = i; k <= j; ++k) if (e[k].use) {
			int u = e[k].u, v = e[k].v;
			ufs.merge(u, v);
		}
		i = j;
	}
	printf("%d\n%s\n", tot, unique ? "Yes" : "No");
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; ++i) {
		scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);	
		e[i].use = 0;
	}
	Kruskal();
	return 0;
}
