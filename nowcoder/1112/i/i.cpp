#include <bits/stdc++.h>
using namespace std;
using pII = pair<int, int>;
#define fi first
#define se second
const int N = 1e5 + 10;
//cnt[i][0] 表示非当前子树中的颜色i的数量
//cnt[i][1] 表示当前子树中的颜色i的数量
int n, c[N], cnt[N][2], ans[N];

struct Graph {
	struct E { int to, nx, id; }e[N << 1]; int h[N], cnt;
	void init(int n) { for (int i = 0; i <= n; ++i) h[i] = -1; cnt = -1; }
	void addedge(int u, int v, int id = 0) { e[++cnt] = { v, h[u], id}; h[u] = cnt; } 
}G;

namespace DSUOnTree {
	int fa[N], sze[N], son[N], son_id[N], big[N], res; 
	void dfs(int u) {
		sze[u] = 1; son[u] = 0;
		for (int i = G.h[u]; ~i; i = G.e[i].nx) {
			int v = G.e[i].to, id = G.e[i].id;
			if (v == fa[u]) continue;
			fa[v] = u;
			dfs(v);
			sze[u] += sze[v];
			if (!son[u] || sze[v] > sze[son[u]]) {
				son[u] = v;
				son_id[u] = id;
			}
		}
	}
	void add(int u, int opt) {
		if (cnt[c[u]][0] && cnt[c[u]][1]) --res;
		if (opt) {
			--cnt[c[u]][0];
			++cnt[c[u]][1];
		} else {
			++cnt[c[u]][0];
			--cnt[c[u]][1];
		}
		if (cnt[c[u]][0] && cnt[c[u]][1]) ++res;
	}
	void up(int u, int opt) {
		add(u, opt);
		for (int i = G.h[u]; ~i; i = G.e[i].nx) {
			int v = G.e[i].to;
			//如果v被标记为重儿子，那么它的贡献已经在里面了
			if (big[v] || v == fa[u]) continue;
			up(v, opt);
		}
	}
	void solve(int u, int id) {
		//先处理完轻儿子的答案
		for (int i = G.h[u]; ~i; i = G.e[i].nx) {
			int v = G.e[i].to, id = G.e[i].id;
			if (v == fa[u] || v == son[u]) continue;
			solve(v, id);
		}
		//再处理重儿子的答案
		if (son[u]) {
			big[son[u]] = 1;
			solve(son[u], son_id[u]);
		}
	    //重新加上轻儿子的贡献和当前点的贡献	
		up(u, u); 
		ans[id] = res;
		if (son[u]) big[son[u]] = 0;
		//如果当前点不是其父亲的重儿子，那么删除它对答案的影响
		if (!big[u]) up(u, 0);
	}
	void gao() {
		res = 0;
		dfs(1);
		solve(1, 0);
	}
};

int main() {
	while (scanf("%d", &n) != EOF) {
		memset(cnt, 0, sizeof cnt);
		G.init(n);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", c + i);
			++cnt[c[i]][0];
		}
		for (int i = 1, u, v; i < n; ++i) {
			scanf("%d%d", &u, &v);
			G.addedge(u, v, i);
			G.addedge(v, u, i);
		}
		DSUOnTree::gao();
		for (int i = 1; i < n; ++i) printf("%d\n", ans[i]);
	}
	return 0;
}
