#include <bits/stdc++.h>
using namespace std;
#define debug(...) { printf("#  "); printf(__VA_ARGS__); puts(""); }
#define pii pair <int, int>
#define fi first
#define se second
const int N = 1e6 + 10;
int n, m, need;
vector <vector<pii>> G;

struct DFS {
	int fa[N], deep[N], vis[N], edge[N]; 
	void Dfs(int u) {
		for (auto it : G[u]) {
			int v = it.fi;
			int id = it.se;
			if (vis[v]) continue;
			fa[v] = u;
			deep[v] = deep[u] + 1;
			edge[v] = id;
			vis[v] = 1;
			Dfs(v); 
		}
	}
	bool work() {
		for (int i = 0; i <= n; ++i) vis[i] = 0;
		for (int i = 1; i <= n; ++i) {
			if (!vis[i]) {
				vis[i] = 1;
				deep[i] = 0;
				fa[i] = i;
				Dfs(i);
			}
		}
		for (int i = 0; i <= n; ++i) vis[i] = 0;
		vector <int> vec, res;
		for (int i = 1; i <= n; ++i) vec.push_back(i);
		sort(vec.begin(), vec.end(), [&](int x, int y){
			return deep[x] > deep[y]; 			
		});
		for (auto &it : vec) {
			if (!vis[it] && fa[it] != it && !vis[fa[it]]) {
				res.push_back(edge[it]);
				vis[it] = 1;
				vis[fa[it]] = 1;
			}
		}
		if ((int)res.size() >= need) {
			puts("Matching");
			for (int i = 0; i < need; ++i) 
				printf("%d%c", res[i], " \n"[i == need - 1]);
			return 1;
		}
		return 0;
	}
}dfs;

struct BFS {
	vector <int> vec, res;  
	int deep[N], vis[N];   
	void Dfs(int u) {
		vec.push_back(u);
		for (auto it : G[u]) {
			int v = it.fi;
			if (vis[v]) continue;
			deep[v] = deep[u] + 1;
			vis[v] = 1;
			Dfs(v); 
		}
	}
	bool work() {
		res.clear();
		for (int i = 0; i <= n; ++i) vis[i] = 0;
		for (int i = 1; i <= n; ++i) {
			if (!vis[i]) {
				vec.clear();
				deep[i] = 0; 
				vis[i] = 1;
				Dfs(i);
				sort(vec.begin(), vec.end(), [&](int x, int y) {
					return deep[x] > deep[y];		
				});
				for (auto it : vec) vis[it] = 0;
				for (auto it : vec) {
					if (!vis[it]) {
						res.push_back(it);
						vis[it] = 1;
						for (auto it2 : G[it]) {
							vis[it2.fi] = 1; 
						}
					}
				}
				for (auto it : vec) vis[it] = 1;
			}
		}
		if ((int)res.size() >= need) {
			puts("IndSet");
			for (int i = 0; i < need; ++i) 
				printf("%d%c", res[i], " \n"[i == need - 1]);
			return 1;
		} 
		return 0;
	}
}bfs;

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		need = n; n *= 3;
		G.clear(); G.resize(n + 1);
		for (int i = 1, u, v; i <= m; ++i) {
			scanf("%d%d", &u, &v);
			G[u].push_back(pii(v, i));
			G[v].push_back(pii(u, i));
		}
		if (dfs.work()) continue;
		if (bfs.work()) continue;
		puts("Impossible");
	}	
	return 0;
}
