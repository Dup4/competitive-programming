#include <bits/stdc++.h>
using namespace std;
#define SZ(x) (int(x.size()))
const int N = 1e3 + 10;
int n, m, c;
struct E {
	int u, v, w;
	bool operator < (const E &other) const {
		return w < other.w;
	}
}e[N * N];

inline int ceil(int x, int y) { if (x % y == 0) return x / y + 1; return (x + y - 1) / y; }

struct UFS {
	int fa[N], sze[N], Max[N], MinID[N];
	void init(int n) {
		for (int i = 1; i <= n; ++i) {
			fa[i] = 0;
			sze[i] = 1;
			Max[i] = 0;
			MinID[i] = i;
		}
	}
	int find(int x) { return fa[x] == 0 ? x : fa[x] = find(fa[x]); }
	void merge(int x, int y, int _Max) {
		x = find(x), y = find(y);
		if (x != y) {
			fa[x] = y;
			sze[y] += sze[x];
			Max[y] = _Max;
			MinID[y] = min(MinID[y], MinID[x]);
		}
	}
	bool same(int u, int v) { return find(u) == find(v); }
	int H(int u) {
		u = find(u);
		return Max[u] + c / sze[u];
		//ceil(c, sze[u]);
	}
}ufs;

void gao() {
	sort(e + 1, e + 1 + m);
	ufs.init(n);
	for (int i = 1; i <= m; ++i) {
		int u = e[i].u, v = e[i].v, w = e[i].w;
		if (ufs.same(u, v)) continue;
		if (w <= ufs.H(u) && w <= ufs.H(v)) {
			ufs.merge(u, v, w);
		}
	}
	vector <vector<int>> vec(n + 5);
	for (int i = 1; i <= n; ++i) {
		vec[ufs.MinID[ufs.find(i)]].push_back(i);
	}
	for (auto &it : vec) if (!it.empty()) {
		sort(it.begin(), it.end());
		for (int i = 0; i < SZ(it); ++i)
			printf("%d%c", it[i] - 1, " \n"[i == SZ(it) - 1]);
	}
}

int main() {
	scanf("%d%d%d", &n, &m, &c);
	for (int i = 1; i <= m; ++i) {
		scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
		++e[i].u, ++e[i].v;
	}
	gao();
	return 0;
}
