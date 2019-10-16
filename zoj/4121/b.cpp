#include <bits/stdc++.h>
using namespace std;
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
using ll = long long;
using pII = pair<int, int>;
#define fi first
#define se second
const int N = 3e5 + 10, M = 23, INF = 0x3f3f3f3f;
int n; ll res;
vector <vector<int>> G;
template <class T1, class T2> void chmax(T1 &x, T2 y) { if (x < y) x = y; }
template <class T1, class T2> void chmin(T1 &x, T2 y) { if (x > y) x = y; }

struct E {
	int ma, mi;
	E(int ma = -INF, int mi = INF) : ma(ma), mi(mi) {}
	void up(E other) {
		chmax(ma, other.ma);
		chmin(mi, other.mi); 
	}
}f[N], g[N]; 
//f 表示路径(i, i - 1) g 表示路径(i, i + 1)

struct W {
	int op, ma, mi;
	W() {}
	W(int op, int ma, int mi) : op(op), ma(ma), mi(mi) {}
}w[N];

struct LCA {
	int fa[N][M], deg[N]; E e[N][M]; 
	void bfs() {
		queue <int> que;
		deg[1] = 0; fa[1][0] = 1;
		e[1][0] = E(-INF, INF); 
		que.push(1); 
		while (!que.empty()) {
			int u = que.front(); que.pop();
			for (int i = 1; i < M; ++i) {
				e[u][i] = E(-INF, INF);
				e[u][i].up(e[u][i - 1]); 
				e[u][i].up(e[fa[u][i - 1]][i - 1]);
				fa[u][i] = fa[fa[u][i - 1]][i - 1]; 
			}
			for (auto &v : G[u]) {
				if (v == fa[u][0]) continue;
				deg[v] = deg[u] + 1;
				fa[v][0] = u;
			    e[v][0] = E(v, v);	
				que.push(v);
			}
		}
	}
	E dis(int u, int v) {
		if (u == v) return E(u, u);
		if (deg[u] > deg[v]) swap(u, v);
		int hu = deg[u], hv = deg[v], tu = u, tv = v;
		E res = E(-INF, INF); 
		for (int det = hv - hu, i = 0; det; det >>= 1, ++i) {
			if (det & 1) {
				res.up(e[tv][i]);
				tv = fa[tv][i]; 
			}
		}
		if (tu == tv) {
			res.up(E(tu, tu));
			return res;
		}
		for (int i = M - 1; i >= 0; --i) {
			if (fa[tu][i] == fa[tv][i]) continue;
			res.up(e[tu][i]);
			res.up(e[tv][i]);
			tu = fa[tu][i]; tv = fa[tv][i];
		}
		res.up(e[tu][0]);
		res.up(e[tv][0]);
		res.up(E(fa[tu][0], fa[tu][0]));
		return res;
	}
}lca;

struct BIT {
	int a[N], pos[N], POS;
	void init() { POS = 0; }
	void update(int x) {
		for (; x <= n + 1; x += x & -x) {
			if (pos[x] < POS) {
				pos[x] = POS;
				a[x] = 1;
			} else {
				++a[x];
			}
		}
	}
	int query(int x) {
		int res = 0;
		for (; x > 0; x -= x & -x) {
			if (pos[x] == POS)
				res += a[x];
		}
		return res;
	}
	int query(int l, int r) {
		if (l > r) return 0;
		return query(r) - query(l - 1);
	}
}bit;

void gao(int l, int r) {
	if (l == r) {
		++res;
		return;
	}
	int mid = (l + r) >> 1;
	gao(l, mid); gao(mid + 1, r);
	E now = E(mid, mid); 
	int cw = 0; 
	for (int i = mid + 1; i <= r; ++i) {
		now.up(f[i]);
		if (now.ma == i) {
			w[++cw] = W(0, now.ma, now.mi); 
		}
	}	
	now = E(mid, mid); 
	for (int i = mid; i >= l; --i) {
		if (i < mid) now.up(g[i]);
		if (now.mi == i) {
			w[++cw] = W(1, now.ma, now.mi);
		}
	}
	sort(w + 1, w + 1 + cw, [&](W x, W y){
		if (x.mi != y.mi)
			return x.mi > y.mi;
		return x.op < y.op;		
	});
	++bit.POS;
	for (int i = 1; i <= cw; ++i) {
		if (w[i].op == 0) {
			bit.update(w[i].ma);
		} else {
			res += bit.query(w[i].ma, n);	
		}
	} 
}

int main() {
	bit.init();
	int _T; scanf("%d", &_T);
	while (_T--) {
		scanf("%d", &n);
		G.clear(); G.resize(n + 1);
		for (int i = 1, u, v; i < n; ++i) {
			scanf("%d%d", &u, &v);
			G[u].push_back(v);
			G[v].push_back(u);
		}
		lca.bfs();
		for (int i = 1; i <= n; ++i) f[i] = g[i] = E(-INF, INF);
		for (int i = 2; i <= n; ++i) f[i] = lca.dis(i - 1, i);
		for (int i = n - 1; i >= 1; --i) g[i] = lca.dis(i, i + 1);
	//	for (int i = 1; i <= n; ++i) dbg(i, f[i].ma, f[i].mi, g[i].ma, g[i].mi);
		res = 0;
		gao(1, n); 	
		printf("%lld\n", res);
	}
	return 0;
}
