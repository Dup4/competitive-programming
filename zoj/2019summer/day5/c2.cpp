#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
int n, q, k, m, w[N];
vector <vector<int>> G[2];
int a[N << 2], Sta[N << 2], vis[N];
ll f[N][2], f2[N][4];  
int fa[N], deep[N], sze[N], son[N], top[N], in[N], out[N], cnt_in;
void DFS(int u) {
	sze[u] = 1;
	for (auto v : G[0][u]) if (v != fa[u]) {
		deep[v] = deep[u] + 1;
		fa[v] = u;
		DFS(v);
		sze[u] += sze[v];
		if (!son[u] || sze[v] > sze[son[u]]) {
			son[u] = v;
		}	
	}
}
void gettop(int u, int tp) {
	top[u] = tp;
	in[u] = ++cnt_in; 
	if (!son[u]) {
		out[u] = cnt_in;
		return;
	}
	gettop(son[u], tp);
	for (auto v : G[0][u]) if (v != fa[u] && v != son[u]) {
		gettop(v, v);
	}
	out[u] = cnt_in;
}
int query(int u, int v) {
	while (top[u] != top[v]) {
		if (deep[top[u]] < deep[top[v]]) {
			swap(u, v);
		}
		u = fa[top[u]];
	}
	if (deep[u] > deep[v]) swap(u, v);
	return u;
}

// 0 不选
// 1 选
void dp(int u, int pre) {
	f[u][0] = f[u][1] = 0;
	if (vis[u]) { 
		f[u][1] = w[u]; 
	} 
	for (auto v : G[1][u]) {
		if (v != pre) {
			dp(v, u);
			f[u][0] += max(f[v][0], f[v][1]);
			if (fa[v] == u) {
				f[u][1] += f[v][0];  
			} else {
				f[u][1] += max(f[v][0], f[v][1]);
			}
		}
	}
}


// 0 表示选择本身
// 1 表示选择的最近的点离根距离为1
// 2 表示选择的最近的点离根距离为2
// 3 ............................3
void dp2(int u, int pre) {
	f2[u][0] = f2[u][1] = f2[u][2] = f2[u][3] = 0;
	if (vis[u]) f2[u][0] = w[u];
	for (auto v : G[1][u]) {
		if (v != pre) {
			dp2(v, u);
			int dep = deep[v] - deep[u]; 
			for (int i = 0; i < 4; ++i) {
				ll Max = 0; 
				for (int j = 0; j < 4; ++j) {
					if (dep + j + i > 2) {
						Max = max(Max, f2[v][j]);	
					}
				}
				f2[u][i] += Max; 
			}
		}
	}
}

void init() {
	cnt_in = 0; fa[1] = 0; deep[1] = 0;
	G[0].clear(); G[0].resize(n + 1); 
	G[1].clear(); G[1].resize(n + 1);
	for (int i = 1; i <= n; ++i) son[i] = 0, vis[i] = 0;
}
int main() {
	scanf("%d%d", &n, &q);
	init();
	for (int i = 1; i <= n; ++i) {
		scanf("%d", w + i);
	}
	for (int i = 1, u, v; i < n; ++i) {
		scanf("%d%d", &u, &v);
		G[0][u].push_back(v);
		G[0][v].push_back(u);
	}
	DFS(1); gettop(1, 1);
	while (q--) {
		scanf("%d%d", &k, &m);
		a[0] = m;
		for (int i = 1; i <= m; ++i) {
			scanf("%d", a + i);
			vis[a[i]] = 1;
		}
		sort(a + 1, a + 1 + m, [&](int x, int y) {
			return in[x] < in[y];		
		});
		for (int i = m; i > 1; --i) {
			a[++a[0]] = query(a[i], a[i - 1]);
		}
		sort(a + 1, a + 1 + a[0], [&](int x, int y){
			return in[x] < in[y];		
		});
		a[0] = unique(a + 1, a + 1 + a[0]) - a - 1; 
		for (int i = 1, top = 0; i <= a[0]; ++i) {
			while (top && out[Sta[top]] < in[a[i]]) {	
				--top;
			}
			if (top) {
				G[1][Sta[top]].push_back(a[i]);
				G[1][a[i]].push_back(Sta[top]);
			}
			Sta[++top] = a[i];
		}
		if (k == 1) {
			dp(a[1], a[1]);
			printf("%lld\n", max(f[a[1]][0], f[a[1]][1])); 
		} else {
			dp2(a[1], a[1]);
			ll res = 0;  
			for (int i = 0; i < 4; ++i) res = max(res, f[a[1]][i]);
			printf("%lld\n", res);
		}
		for (int i = 1; i <= a[0]; ++i) {
			vis[a[i]] = 0;
			G[1][a[i]].clear();
		}	
	}
	return 0;
}
