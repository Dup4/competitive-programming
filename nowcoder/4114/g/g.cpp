#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pII = pair<int, int>; 
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
#define fi first
#define se second
const int N = 5e5 + 10;
int n, K, vis[N], fa[N]; 
vector <vector<pII>> G;

struct E {
	ll val, Max, sMax;
	int sze;
}f[N], g[N];

void dfs(int u) {
	f[u].sze += vis[u];
	for (auto &it : G[u]) {
		int v = it.fi, w = it.se;
		if (v == fa[u]) continue;
		fa[v] = u;
		dfs(v);
		f[u].sze += f[v].sze; 
		f[u].val += f[v].val; 
		if (f[v].sze) f[u].val += w;
		if (f[v].sze) { 
			if (f[v].Max + w > f[u].Max) {
				f[u].sMax = f[u].Max;
				f[u].Max = f[v].Max + w;
			} else if (f[v].Max + w > f[u].sMax) {
				f[u].sMax = f[v].Max + w;
			}
		}
	}
}

void dfs1(int u) {
	for (auto &it : G[u]) {
		int v = it.fi, w = it.se;
		if (v == fa[u]) continue;
		g[v].sze += g[u].sze + f[u].sze - f[v].sze; 
		g[v].val += g[u].val + f[u].val - f[v].val;
		if (g[u].sze + f[u].sze - f[v].sze) g[v].val += w; 
		if (f[v].sze) g[v].val -= w;
		if (g[u].sze) {
			if (g[u].Max + w > g[v].Max) {
				g[v].sMax = g[v].Max;
				g[v].Max = g[u].Max + w;
			} else if (g[u].Max + w > g[v].sMax) {
				g[v].sMax = g[u].Max + w;
			}
		}
		if (f[u].sze - f[v].sze) {
			int Max;
			if (f[u].Max == f[v].Max + w) {
				Max = f[u].sMax;
			} else {
				Max = f[u].Max; 
			}
			if (Max + w > g[v].Max) {
				g[v].sMax = g[v].Max;
				g[v].Max = Max + w;
			} else if (Max + w > g[v].sMax) {
				g[v].sMax = Max + w;
			}
		}
		dfs1(v);
	}
}

int main() {
	while (scanf("%d%d", &n, &K) != EOF) {
		G.clear(); G.resize(n + 1);
		for (int i = 1, u, v, w; i < n; ++i) {
			scanf("%d%d%d", &u, &v, &w);
			G[u].push_back(pII(v, w));
			G[v].push_back(pII(u, w));
		}
		memset(vis, 0, sizeof vis);
		for (int i = 1, x; i <= K; ++i) {
			scanf("%d", &x);
			vis[x] = 1; 
		}
		dfs(1); 
		dfs1(1);
		for (int i = 1; i <= n; ++i) {
			printf("%lld\n", 2ll * (g[i].val + f[i].val) - max(g[i].Max, f[i].Max));
			//dbg(i, g[i].val, f[i].val, f[i].Max, g[i].Max);
		} 
	}
	return 0;
}
