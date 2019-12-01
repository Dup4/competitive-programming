#include <bits/stdc++.h>
using namespace std;
using pII = pair<int, int>;
#define fi first
#define se second
mt19937 rnd(time(0));
const int N = 2e5 + 10, M = 20;
int n, m, in[N], out[N], vis[N];
vector <vector<int>> G;
vector <int> po;
struct LCA {
	int F[N << 1], P[N], dep[N];
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
	void dfs(int u, int pre) {
		in[u] = ++*in;
		F[++*F] = u;
		st.rmq[*F] = dep[u];
		P[u] = *F;
		for (auto &v : G[u]) if (v != pre) {
			dep[v] = dep[u] + 1;
			dfs(v, u);
			F[++*F] = u;
			st.rmq[*F] = dep[u];
		}
		out[u] = *in;
	}
	void init(int rt, int node_num) {
		*F = 0;
		*in = 0;
		dep[rt] = 0;
		dfs(rt, rt);
		st.init(2 * node_num - 1);
	}
	int query(int u, int v) { return F[st.queryMin(P[u], P[v])]; }
	int dis(int u, int v) { return dep[u] + dep[v] - 2 * dep[query(u, v)]; }
}lca;

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		G.clear(); G.resize(n + 1);
		po.clear();
		memset(vis, 0, sizeof vis);
		for (int i = 1, u, v; i < n; ++i) {
			scanf("%d%d", &u, &v);
			G[u].push_back(v);
			G[v].push_back(u);
		}
		for (int i = 1, x; i <= m; ++i) {
			scanf("%d", &x);
			vis[x] = 1;
			po.push_back(x);
		}
		if (m == n) {
			if (n == 1) puts("YES\n1");
			else puts("NO");
		} else {
			if (m == 1) {
				printf("YES\n%d\n", po[0]);
				continue;
			}
			int rt = 1;
			for (int i = 1; i <= n; ++i) {
				if (vis[i] == 0) {
					rt = i;
					break;
				}
			}
			lca.init(rt, n);
			int LCA = po[0];
			for (int i = 1; i < m; ++i) {
				LCA = lca.query(LCA, po[i]);
			}
			shuffle(po.begin(), po.end(), rnd);
			//sort(po.begin(), po.end(), [&](int x, int y) { return in[x] < in[y]; });
			vector <pII> vec;
			for (int i = 1; i <= n; ++i) {
				if (vis[i] == 0 && in[i] >= in[LCA] && in[i] <= out[LCA]) {
					vec.push_back(pII(i, lca.dis(i, po[0])));
				}
			}
			for (int i = 1; i < m && ! vec.empty(); ++i) {
				vector <pII> buf;
				for (auto &it : vec) {
					if (lca.dis(po[i], it.fi) == it.se) {
						buf.push_back(it);
					}
				}
				vec = buf;
			}
			if (vec.empty()) puts("NO");
			else printf("YES\n%d\n", vec[0].fi);
		}
	}
	return 0;
}
