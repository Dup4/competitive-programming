#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int n, q;
int a[N << 1], Sta[N << 1], vis[N]; 
vector <vector<int>> G[2];  

namespace Tree {
	int fa[N], deep[N], sze[N], son[N], top[N], in[N], out[N], Sta[N << 1];
	int f[N], g[N];
	void dfs(int u) {
		son[u] = 0; sze[u] = 1;
		for (auto &v : G[0][u]) {
			if (v == fa[u]) continue;
			fa[v] = u;
			deep[v] = deep[u] + 1;
			dfs(v);
			sze[u] += sze[v];
			if (!son[u] || sze[v] > sze[son[u]]) son[u] = v;
		}
	}
	void gettop(int u, int tp) {
		in[u] = ++*in;
		top[u] = tp;
		if (son[u]) gettop(son[u], tp);
		for (auto &v : G[0][u]) {
			if (v != son[u] && v != fa[u])
				gettop(v, v);
		}
		out[u] = *in;
	}
	int querylca(int u, int v) {
		while (top[u] != top[v]) {
			if (deep[top[u]] < deep[top[v]]) swap(u, v);
			u = fa[top[u]];
		}
		if (deep[u] > deep[v]) swap(u, v);
		return u;
	}
	void init() {
		fa[1] = 0; deep[1] = 0; *in = 0;
		dfs(1); gettop(1, 1);
	}
	void dp(int u, int fa) {
		//将用到的点加入a[]，方便清空
		a[++*a] = u;
		a[++a[0]] = u;
		f[u] = g[u] = 0;  
		for (auto &v : G[1][u]) {
			if (v == fa) continue;
			dp(v, u); 
			f[u] += f[v];
			g[u] += g[v];
		}
		if (vis[u]) {
			f[u] += g[u];
			g[u] = 1;
		} else {
			f[u] += (g[u] > 1);
			g[u] = (g[u] == 1);
		}
	}
	bool Not() {
		for (int i = 1; i <= *a; ++i) {
			if (vis[fa[a[i]]]) {
				return true;
			}
		}
		return false;
	}
	void gao() {
		if (Not()) {
			puts("-1");
			return;
		}
		int k = *a, top;
		sort(a + 1, a + 1 + k, [&](int x, int y) {
			return in[x] < in[y];		
		});
		//超级根
		Sta[top = 1] = 1; 
		for (int i = 1; i <= k; ++i) {
			//求出当前点与栈顶元素的lca
			int lca = querylca(a[i], Sta[top]);  
			//1. lca = Sta[top] 说明a[i] -> Sta[top]是一条直链，直接将a[i]加入栈即可
			//2. lca != Sta[top] 说明a[i]和Sta[top]在不同的子树中
			//那么我们要维护一条链，那么栈中深度比当前点lca的深度大的都要出栈并且连变
			//再把lca加进去，栈中的所有点又是一条链
			while (deep[lca] < deep[Sta[top]]) {
				if (deep[Sta[top - 1]] <= deep[lca]) {
					int last = Sta[top--];
					if (Sta[top] != lca) {
						Sta[++top] = lca;
					}
					G[1][last].push_back(lca);
					G[1][lca].push_back(last);
					break;
				}
				G[1][Sta[top]].push_back(Sta[top - 1]);
				G[1][Sta[top - 1]].push_back(Sta[top]);
				--top;
			}
			if (Sta[top] != a[i]) Sta[++top] = a[i];
		}	
		while (top > 1) {
			G[1][Sta[top]].push_back(Sta[top - 1]);
			G[1][Sta[top - 1]].push_back(Sta[top]);
			--top;
		}
		*a = 0;
		dp(1, 1);
		printf("%d\n", f[1]);
	}
}

int main() {
	while (scanf("%d", &n) != EOF) {
		G[0].clear(); G[0].resize(n + 1);
		G[1].clear(); G[1].resize(n + 1);
		memset(vis, 0, sizeof vis);
		for (int i = 1, u, v; i < n; ++i) {
			scanf("%d%d", &u, &v);
			G[0][u].push_back(v);
			G[0][v].push_back(u);
		}
		Tree::init();
		scanf("%d", &q);
		while (q--) {
			scanf("%d", a);  
			for (int i = 1; i <= *a; ++i) {
				scanf("%d", a + i);
				vis[a[i]] = 1;   
			}
			Tree::gao();
			//清空操作
			for (int i = 1; i <= *a; ++i) {
				vis[a[i]] = 0;
				G[1][a[i]].clear();
			}
		}
	}
	return 0;
}
