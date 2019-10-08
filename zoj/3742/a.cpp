#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pII = pair <int, int>;
#define fi first
#define se second
const int N = 5e4 + 10, S = 300;
int n, m, q, e[N][3], d[N], big[N], bigp[N];
ll f[N][2], g[2];  //0 + 1 -
vector <vector<pII>> G;

int main() {
	while (scanf("%d%d%d", &n, &m, &q) != EOF) {
		for (int i = 0; i <= n; ++i) {
			d[i] = big[i] = 0;
			f[i][0] = f[i][1] = 0;
		}
		*bigp = 0; g[0] = g[1] = 0;
		G.clear(); G.resize(n + 1);
		for (int i = 1; i <= m; ++i) {
			scanf("%d%d%d", e[i], e[i] + 1, e[i] + 2);
			++d[e[i][0]]; ++d[e[i][1]];
		}
		for (int i = 1; i <= n; ++i) {
			if (d[i] >= S) bigp[++*bigp] = i;
		}
		for (int i = 1; i <= m; ++i) {
			int u = e[i][0], v = e[i][1], w = e[i][2];
			if (big[u] == big[v]) {
				G[u].emplace_back(v, w);
				G[v].emplace_back(u, w);
			} else {
				if (big[u]) swap(u, v);
				G[u].emplace_back(v, w);
				if (w <= 0) f[v][1] += abs(w);
				else f[v][0] += abs(w); 
			}
		}
		for (int u = 1; u <= n; ++u) {
			for (auto &it : G[u]) {
				int v = it.fi, w = it.se;
				if (v > u || big[u] != big[v]) continue;
				if (w < 0) g[1] += abs(w);
				else g[0] += abs(w);
			}
		}

		
	}
	return 0;
}
