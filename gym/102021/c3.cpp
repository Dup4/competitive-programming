#include <bits/stdc++.h>
using namespace std;

#define pii pair <int, int>
#define fi first
#define se second
const int N = 1e3 + 10;
int n, m, res, f[N], d[N];
vector <vector<pii>> G;
struct node {
	int u, w;
	node() {}
	node(int u, int w) : u(u), w(w) {}
	bool operator < (const node &other) const {
		return w > other.w;
	}
};
void gao() {
	priority_queue <node> pq;
	int cnt = 0;
	memset(f, 0, sizeof f);
	for (int i = 1; i <= n; ++i) {
		if (!d[i])
			pq.push(node(i, 0));
	}
	int res = 0;
	while (!pq.empty()) {
		int u = pq.top().u; pq.pop();
		res = max(res, f[u]);
		++cnt;
		for (auto &it : G[u]) {
			int v = it.fi, w = it.se;
			f[v] = max(f[v], f[u] + w);
			if (--d[v] == 0) {
				pq.push(node(v, f[v]));
			}
		}
	}
	assert(cnt == n);
	printf("%d\n", res);
}
int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		G.clear(); G.resize(n + 1);
		memset(d, 0, sizeof d);
		for (int i = 1, u, v, w; i <= m; ++i) {
			scanf("%d%d%d", &u, &v, &w);
			G[u].emplace_back(v, w); 
			++d[v];
		}
		gao();
	}
	return 0;
}
