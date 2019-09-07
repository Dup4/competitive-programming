#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
const int M = 25;
const int mod = 1e9 + 7;
int n, m, q, A, B, C, P;
inline int rnd() { return A = (A * B + C) % P;}
struct Edge {
	int u, v, w;
	Edge () {}
	Edge (int u, int v, int w) : u(u), v(v), w(w) {}
	void scan() {
		scanf("%d%d%d", &u, &v, &w);
	}
	bool operator < (const Edge &other) const {
		return w < other.w;
	}
}e[N];

struct Graph {
	struct node {
		int to, nx;
		node() {}
		node (int to, int nx) : to(to), nx(nx) {}
	}a[N << 1];
	int head[N], pos;
	void init() {
		memset(head, -1, sizeof head);
		pos = 0;
	}
	void add(int u, int v) {
		a[pos] = node(v, head[u]); head[u] = pos++;
	}
}G;
#define erp(u) for (int it = G.head[u], v = G.a[it].to; ~it; it = G.a[it].nx, v = G.a[it].to)

int a[N]; 
struct MST {
	int fa[N], id;
	int find(int u) {
		return fa[u] == u ? u : fa[u] = find(fa[u]);
	}
	void init() {
		for (int i = 1; i <= (n << 1); ++i) {
			fa[i] = i;
		}
		id = n;
	}
	void Kruskal() {
		G.init(); init();
		for (int i = 1; i <= m; ++i) {
			int u = find(e[i].u), v = find(e[i].v), w = e[i].w;
			if (u == v) continue;
			++id; a[id] = w;
			G.add(id, u);
			G.add(id, v);
			fa[u] = fa[v] = id;
		}
	}
}mst;

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
	void DFS(int u, int pre, int dep) {
		F[++*F] = u;
		st.rmq[*F] = dep;
		P[u] = *F;
		erp(u) if (v != pre) {
			DFS(v, u, dep + 1);
			F[++*F] = u;
			st.rmq[*F] = dep;
		}
	}
	void init(int root, int node_num) {
		*F = 0;
		DFS(root, root, 0);
		st.init(2 * node_num - 1);
	}
	int query(int u, int v) { return F[st.queryMin(P[u], P[v])]; }
}lca;

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		for (int i = 1; i <= m; ++i) e[i].scan();
		scanf("%d%d%d%d%d", &q, &A, &B, &C, &P);
		sort(e + 1, e + 1 + m);
		mst.Kruskal();
		lca.init(mst.id, mst.id);
		int ans = 0;
		for (int i = 1, u, v; i <= q; ++i) {
			u = rnd() % n + 1, v = rnd() % n + 1;
			ans += a[lca.query(u, v)]; 
			ans %= mod;
		}
		printf("%d\n", ans);
	}
	return 0;
}
