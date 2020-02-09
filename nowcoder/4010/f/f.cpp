#include <bits/stdc++.h>
using namespace std;
using pII = pair<int, int>;
using ll = long long;
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
#define fi first
#define se second
const int N = 1e6 + 5, M = 21, S = 1000; 
int n, q, e[N][3]; 
vector <vector<int>> G, U, D;
int fa[N][M], deep[N], md[N], len[N], son[N], top[N], hbit[N], val[N], in[N], out[N]; 
ll res[N], tot, add[N], sze[N];
void DFS(int u, int ff) {
	in[u] = ++*in;
	fa[u][0] = ff;
	md[u] = deep[u] = deep[ff] + 1;
	for (int i = 1; i < M; ++i) {
		if (fa[u][i - 1]) {
			fa[u][i] = fa[fa[u][i - 1]][i - 1];
		} else {
			break;
		}
	}
	for (auto v : G[u]) { 
		if (v != ff) {
			DFS(v, u);
			if (md[v] > md[son[u]]) {
				son[u] = v;
				md[u] = md[v]; 
			} 
		}
	}
	out[u] = *in;
}
void gettop(int u, int tp) {
	top[u] = tp;
	len[u] = md[u] - deep[top[u]] + 1;
	if (!son[u]) return;
	gettop(son[u], tp);
	for (auto v : G[u]) if (v != fa[u][0] && v != son[u]) {
		gettop(v, v); 
	}
}

int queryKth(int u, int k) {
	if (!k) return u;
	if (k > deep[u]) return 0;
	u = fa[u][hbit[k]]; k ^= (1 << hbit[k]);
	if (!k) return u;
	if (deep[u] - deep[top[u]] == k) return top[u];
	if (deep[u] - deep[top[u]] > k) return D[top[u]][deep[u] - deep[top[u]] - k - 1]; 
	return U[top[u]][k - deep[u] + deep[top[u]] - 1]; 
}

void init() {
	G.clear(); G.resize(n + 1);
	U.clear(); U.resize(n + 1);
	D.clear(); D.resize(n + 1);
	memset(deep, 0, sizeof deep);
	memset(son, 0, sizeof son);
	memset(fa, 0, sizeof fa);
	memset(md, 0, sizeof md);
	memset(add, 0, sizeof add);
	*in = 0;
	for (int i = 1, mx = 1; i <= n; ++i) {
		if (i >> mx & 1) ++mx;
		hbit[i] = mx -1;
	}
	md[1] = deep[1] = 1; 
}

void work(int u) {
	res[u] = 0;
	sze[u] = add[u];  
	for (auto &v : G[u]) if (v != fa[u][0]) {
		work(v);
		sze[u] += sze[v];
		res[u] += sze[v] * val[v];
	}
}

int main() {
	while (scanf("%d", &n) != EOF) {
		init();
		for (int i = 1, u, v, w; i < n; ++i) {
			scanf("%d%d%d", &u, &v, &w);
			e[i][0] = u; e[i][1] = v; e[i][2] = w;
			G[u].push_back(v);
			G[v].push_back(u);
		}
		DFS(1, 0); gettop(1, 1);
		for (int i = 1; i <= n; ++i) {
			if (i == top[i]) {
				int it = i;
				for (int j = 1; it && j <= len[i]; ++j) {
					it = fa[it][0]; 
					U[i].push_back(it); 
				}
				it = i;
				for (int j = 1; j <= len[i]; ++j) {
					it = son[it];
					D[i].push_back(it);
				}
			}
		}
		for (int i = 1; i < n; ++i) {
			if (fa[e[i][0]][0] == e[i][1]) val[e[i][0]] = e[i][2];
			else val[e[i][1]] = e[i][2]; 
		}
	//	for (int i = 1; i <= n; ++i) dbg(i, val[i]);
		tot = 0;
		vector <pII> opvec;
		scanf("%d", &q);
		int rt = 1; 
		ll ans = 0;
		for (int _q = 1, op, v, x; _q <= q; ++_q) { 
			scanf("%d%d", &op, &v); 
			if (op == 1) {
				scanf("%d", &x);
				opvec.push_back(pII(v, x));
				if (in[v] >= in[rt] && in[v] <= out[rt]) { 
					if (v != rt) {
						int kth = queryKth(v, deep[v] - deep[rt] - 1); 
						ans += 1ll * x * val[kth];
					}
				} else {
					ans += 1ll * x * val[rt]; 
				}
			} else {
				if (opvec.size() > S) {
					for (auto &it : opvec) {
						tot += it.se;
						add[it.fi] += it.se; 
					}
					opvec.clear(); 
					work(1); 
					rt = v;
					ans = res[rt];
					ans += 1ll * val[rt] * (tot - sze[rt]);
				} else {
					rt = v; 
					ans = res[rt];
					ans += 1ll * val[rt] * (tot - sze[rt]);
					for (auto &it : opvec) {
						int v = it.fi, x = it.se;
						if (in[v] >= in[rt] && in[v] <= out[rt]) {
							if (v == rt) continue;
							int kth = queryKth(v, deep[v] - deep[rt] - 1);
							ans += 1ll * x * val[kth]; 
						} else {
							ans += 1ll * x * val[rt]; 
						}
					}
				}
			}
			printf("%lld\n", ans);
		}
	}
	return 0;
}
