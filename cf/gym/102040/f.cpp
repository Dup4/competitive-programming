#include <bits/stdc++.h>
using namespace std;
using pII = pair<int, int>;
#define fi first
#define se second
const int N = 1e5 + 10, M = 20;
vector <vector<int>> G;

int n, q, fa[N], dep[N];
struct LCA {
	int F[N << 1], P[N];
	struct RMQ {
		int Min[N << 1][M];
		int mm[N << 1], rmq[N << 1];
		void init(int n) {
			mm[0] = -1;
			for (int i = 1; i <= n; ++i) {
				mm[i] = ((i & (i - 1)) == 0) ? mm[i - 1] + 1 : mm[i - 1];
				Min[i][0] = i;
			}
			for (int j = 1; j <= mm[n]; ++j) {
				for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
					Min[i][j] = rmq[Min[i][j - 1]] < rmq[Min[i + (1 << (j - 1))][j - 1]] ? Min[i][j - 1] : Min[i + (1 << (j - 1))][j - 1];
				}
			}
		}
		int queryMin(int x, int y) {
			if (x > y) swap(x, y);
			int k = mm[y - x + 1];
			return rmq[Min[x][k]] <= rmq[Min[y - (1 << k) + 1][k]] ? Min[x][k] : Min[y - (1 << k) + 1][k];
		}	
	}st;
	void dfs(int u) {
		F[++*F] = u;
		st.rmq[*F] = dep[u];
		P[u] = *F;
		for (auto &v : G[u]) if (v != fa[u]) {
			fa[v] = u;
			dep[v] = dep[u] + 1;
			dfs(v);
			F[++*F] = u;
			st.rmq[*F] = dep[u];
		}
	}
	void init(int rt) {
		*F = 0;
		fa[rt] = rt; dep[rt] = 0;
		dfs(rt);
		st.init(2 * n - 1);
	}
	int query(int u, int v) { return F[st.queryMin(P[u], P[v])]; }
	int dis(int u, int v) { return dep[u] + dep[v] - 2 * dep[query(u, v)] + 1; }
}lca;

pII gao(pII x, pII y) {
	if (x.fi == -1 || y.fi == -1) return pII(-1, -1);
	int t[] = {lca.query(x.fi, y.fi), lca.query(x.fi, y.se), lca.query(x.se, y.fi), lca.query(x.se, y.se)};
	sort(t, t + 4, [&](int x, int y) { return dep[x] < dep[y]; });
	int d[] = {lca.query(x.fi, x.se), lca.query(y.fi, y.se)};
	if (dep[d[0]] > dep[d[1]]) swap(d[0], d[1]);
	if (dep[t[3]] >= dep[t[2]] && dep[t[2]] >= dep[d[1]]) {
		return pII(t[2], t[3]);
	} else {
		return pII(-1, -1);
	}
} 

int main() {
	int _T; scanf("%d", &_T);
	for (int kase = 1; kase <= _T; ++kase) {
		printf("Case %d:\n", kase);
		scanf("%d", &n);
		G.clear(); G.resize(n + 1);
		for (int i = 1, u, v; i < n; ++i) {
			scanf("%d%d", &u, &v);
			G[u].push_back(v);
			G[v].push_back(u);
		}
		lca.init(1);
		scanf("%d", &q);
		int k; pII x, y;
		while (q--) {
			scanf("%d%d%d", &k, &x.fi, &x.se);
			for (int i = 2; i <= k; ++i) {
				scanf("%d%d", &y.fi, &y.se);
				x = gao(x, y);
			}
			if (x.fi == -1) puts("0");
			else printf("%d\n", lca.dis(x.fi, x.se));
		}
	}
	return 0;
}
