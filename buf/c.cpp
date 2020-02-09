#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10, M = 20, INF = 0x3f3f3f3f;
int n, m, q; 

struct E { int to, nx, w; }e[N << 1]; int h[N]; 
void initE(int n) { for (int i = 0; i <= n; ++i) h[i] = 0; }
void addedge(int u, int v, int w) { e[++*h] = { v, h[u], w }; h[u] = *h;}

struct LCA {
	int fa[N][M], dis[N][M]; 
	int deep[N]; 
	void BFS(int rt) {
		queue <int> q; 
		deep[rt] = 0; fa[rt][0] = rt; dis[rt][0] = 0; q.emplace(rt); 
		while (!q.empty()) {
			int u = q.front(); q.pop();  
			for (int i = 1; i < M; ++i) { 
				dis[u][i] = dis[u][i - 1] + dis[fa[u][i - 1]][i - 1];   
				fa[u][i] = fa[fa[u][i - 1]][i - 1]; 
			} 
			for (int i = h[u]; i; i = e[i].nx) {
				int v = e[i].to, w = e[i].w;
				if (v == fa[u][0]) continue;
				deep[v] = deep[u] + 1;   
				fa[v][0] = u; dis[v][0] = w;   
				q.emplace(v);   
			} 
		}
	}
	int querylca(int u, int v) {
		if (u == v) return u;
		if (deep[u] > deep[v]) swap(u, v);
		int hu = deep[u], hv = deep[v], tu = u, tv = v;
		for (int det = hv - hu, i = 0; det; det >>= 1, ++i) {
			if (det & 1) {
				tv = fa[tv][i];
			}
		}	
		if (tu == tv) return tu;
		for (int i = M - 1; i >= 0; --i) {
			if (fa[tu][i] == fa[tv][i]) continue;
			tu = fa[tu][i];
			tv = fa[tv][i];
		}
		return tu;
	}
	int querydis(int u, int v) {
		if (u == v) return 0; 
		if (deep[u] > deep[v]) swap(u, v); 
		int res = 0, hu = deep[u], hv = deep[v], tu = u, tv = v;
		for (int det = hv - hu, i = 0; det; det >>= 1, ++i) {
			if (det & 1) {
				res += dis[tv][i];    
				tv = fa[tv][i];  
			}
		}
		if (tu == tv) return res;    
		for (int i = M - 1; i >= 0; --i) {
			if (fa[tu][i] == fa[tv][i]) continue;
			res += dis[tu][i] + dis[tv][i];  
			tu = fa[tu][i]; tv = fa[tv][i];  
		}
		return res + dis[tu][0] + dis[tv][0];   
	}
}lca;

struct node {
	vector <int> v; int len;  
	inline void scan() {
		scanf("%d", &len); v.clear();   
		for (int i = 1, u; i <= len; ++i) {
			scanf("%d", &u);   
			v.emplace_back(u);   
		} 
	}
}arr[N];

int main() {
	int _T; scanf("%d", &_T);
	while (_T--) {
		scanf("%d%d", &n, &m); 
		initE(n);
		for (int i = 1, u, v, w; i < n; ++i) {
			scanf("%d%d%d", &u, &v, &w); 
			addedge(u, v, w);  
			addedge(v, u, w);
		}	
		lca.BFS(1);
		for (int i = 1; i <= m; ++i) arr[i].scan(); 
		scanf("%d", &q);     
		for (int i = 1, u, v; i <= q; ++i) {
			scanf("%d%d", &u, &v);
			int ans = INF; 
			for (auto it : arr[u].v) 
				for (auto it2 : arr[v].v) 
					ans = min(ans, lca.querydis(it, it2)); 
			printf("%d\n", ans);  
		}
	}
	return 0;
}
