#include <bits/stdc++.h>
using namespace std;
using pII = pair<int, int>;
using ll = long long;
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
#define fi first
#define se second
const int N = 1e6 + 5, S = 800; 
int n, q, e[N][3]; 
vector <vector<int>> G;
int fa[N], deep[N], val[N], in[N], out[N]; 
ll res[N], tot, add[N], sze[N]; 
void DFS(int u) {
	in[u] = ++*in;
	for (auto v : G[u]) if (v != fa[u]) {
	    fa[v] = u;
		deep[v] = deep[u] + 1;	
		DFS(v);
	}
	out[u] = *in;
}

void init() {
	G.clear(); G.resize(n + 1);
	memset(deep, 0, sizeof deep);
	memset(fa, 0, sizeof fa);
	memset(add, 0, sizeof add);
	*in = 0;
}

void work(int u) {
	res[u] = 0;
	sze[u] = add[u];  
	for (auto &v : G[u]) if (v != fa[u]) {
		work(v);
		sze[u] += sze[v];
		res[u] += sze[v] * val[v];
	}
}

int query(int u, int v) {
	int l = 0, r = G[u].size() - 1, res = -1;
	while (r - l >= 0) {
		int mid = (l + r) >> 1;
		if (in[v] >= in[G[u][mid]]) {
			res = mid;
			l = mid + 1;
		} else {
			r = mid - 1;
		}
	}
	return G[u][res];
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
		DFS(1); 
		for (int i = 1; i < n; ++i) {
			if (fa[e[i][0]] == e[i][1]) val[e[i][0]] = e[i][2];
			else val[e[i][1]] = e[i][2]; 
		}
		for (int i = 1; i <= n; ++i) {
			vector <int> tmp;
			for (auto &v : G[i]) {
				if (v == fa[i]) continue;
				tmp.push_back(v);
			}
			G[i] = tmp;
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
						int kth = query(rt, v);
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
							int kth = query(rt, v);
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
