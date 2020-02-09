#include <bits/stdc++.h>
using namespace std;
using pII = pair <int, int>;
using ll = long long;
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
#define fi first
#define se second
const int N = 3e5 + 10;
int n, m, fa[N], deep[N], son[N], top[N], sze[N];
ll A[N], B[N], C[N];
pII a[N];
vector <vector<int>> G;

void pre(int u) {
	sze[u] = 1; son[u] = 0;
	for (auto &v : G[u]) if (v != fa[u]) {
		fa[v] = u;
		deep[v] = deep[u] + 1;
		pre(v);
		sze[u] += sze[v];
		if (!son[u] || sze[v] > sze[son[u]]) son[u] = v;
	}	
}

void gettop(int u, int tp) {
	top[u] = tp;
	if (son[u]) gettop(son[u], tp);
	for (auto &v : G[u]) if (v != fa[u] && v != son[u]) 
		gettop(v, v);
}

int querylca(int u, int v) {
	while (top[u] != top[v]) {
		if (deep[top[u]] < deep[top[v]]) swap(u, v);
		u = fa[top[u]];
	}
	if (deep[u] > deep[v]) swap(u, v);
	return u;
}

void dfs(int u) {
	for (auto &v : G[u]) if (v != fa[u]) {
		dfs(v);
		B[u] += B[v];
		C[u] += C[v];
	}
}

void get(int u) {
	for (auto &v : G[u]) if (v != fa[u]) {
		A[v] = A[u];
		A[v] += B[v];
		A[v] += C[v] * deep[v]; 
		get(v);
	}	
}

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		G.clear(); G.resize(n + 1);
		for (int i = 1, u, v; i < n; ++i) {
			scanf("%d%d", &u, &v);
			G[u].push_back(v);
			G[v].push_back(u);
		}
		fa[1] = deep[1] = 0;
		pre(1); gettop(1, 1);
		memset(A, 0, sizeof A);
		memset(B, 0, sizeof B);
		memset(C, 0, sizeof C);
		for (int i = 1, u, v; i <= m; ++i) {
			scanf("%d%d", &a[i].fi, &a[i].se);
			u = a[i].fi, v = a[i].se;
			int lca = querylca(u, v);
			int len = deep[u] + deep[v] - 2 * deep[lca];
			A[1] += 1ll * (deep[u] - deep[lca]) * (deep[v] - deep[lca]); 
			B[u] += 1 - len + 2 * deep[u]; 
			C[u] += -2;
			B[lca] -= 1 - len + 2 * deep[u];
			C[lca] -= -2;
			B[v] += 1 - len + 2 * deep[v];
			C[v] += -2;
			B[lca] -= 1 - len + 2 * deep[v];
			C[lca] -= -2; 
		}
		dfs(1);
		get(1);
		for (int i = 1; i <= n; ++i)
			printf("%lld\n", A[i]);
	}
	return 0;
}
