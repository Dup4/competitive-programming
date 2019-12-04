#include <bits/stdc++.h>
using namespace std;
using pII = pair<int, int>;
using ll = long long;
#define fi first
#define se second
const int N = 1e5 + 10;
int n, m; ll res, dis[N]; 
vector <vector<int>> G[3], po; 

int id[N]; 
struct UFS {
	int fa[N], sze[N];
	void init() {
		for (int i = 1; i <= n; ++i) {
			fa[i] = 0;
			sze[i] = 1;
		}
	}
	int find(int x) {
		return fa[x] == 0 ? x : fa[x] = find(fa[x]); 
	}
	void merge(int x, int y) {
		int fx = find(x), fy = find(y);
		if (fx != fy) {
			if (sze[fx] > sze[fy]) swap(fx, fy);
			fa[fx] = fy;
			sze[fy] += sze[fx];
		}
	}
}ufs;

int Insta[N]; pII fa[N]; 
void dfs(int u) {
	Insta[u] = 1;
	for (auto &it : G[0][u]) { 
		int v = it.fi, w = it.se;
		if (v == fa[u].fi) continue; 
		if (Insta[v]) {
			int now = u;
			G[2][now].emplace_back(u, w);
			G[2][u].emplace_back(now, w); 
			while (now != v) {
				ufs.merge(now, fa[now].fi);
				res -= fa[now].se; 
				G[2][now].emplace_back(fa[now].fi, fa[now].se); 
				G[2][fa[now].fi].emplace_back(now, fa[now].se); 
				now = fa[now].fi;
			} 
		} else {
			fa[v] = pII(u, w);
			dfs(v); 
		}
	}
	Insta[u] = 0; 
}

void dfs1(int u, int fa) {
	
}

void dfs2(int u, int fa) {
	Insta[u] = 1;
	for (auto &it : G[1][u]) {
		int v = 
	}
}

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		res = 0;
		memset(dis, 0, sizeof dis); 
		for (int i = 0; i < 3; ++i) {
			G[i].clear();
			G[i].resize(n + 1);
		}
		for (int i = 1, u, v, w; i <= m; ++i) {
			scanf("%d%d%d", &u, &v, &w);
			G[0][u].emplace_back(v, w);
			G[0][v].emplace_back(u, w); 
			res += 2 * w;
		}
		ufs.clear();
		fa[1] = pII(0, 0);
		dfs(1);
		*id = 0;
		for (int i = 1; i <= n; ++i) {
			if (ufs.fa[i] == 0) {
				id[i] = ++*id;
			}
		}
		po.clear(); po.resize(*id + 1);
		for (int i = 1; i <= n; ++i) {
			if (ufs.fa[i]) {
				id[i] = id[ufs.find(i)];
			}
			po[id[i]].push_back(i);
		}
		for (int u = 1; u <= n; ++u) { 
			for (auto &it : G[0][u]) {
				int v = it.fi;
				if (id[u] != id[v]) {
					G[2][id[u]].emplace_back(id[v], 0); 
				}
			}
		}
		dis[1] = 0;
		dfs2(1, 1);
		dfs1(id[1], id[1]); 
		ll Max = 0;
		for (int i = 1; i <= n; ++i) {
			Max = max(Max, dis[i]);
		}
		printf("%lld\n", res - Max);
	}
	return 0;
}
