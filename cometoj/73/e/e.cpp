#include <bits/stdc++.h>
using namespace std;
using pII = pair<int, int>;
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
#define fi first
#define se second
const int N = 2e5 + 10, INF = 0x3f3f3f3f;
int n, m, q, f[N][3], g[N][2], vis[N]; 
// 0 Min 1 Max 2 GAP
vector <vector<pII>> G, G1;
inline void chmin(int &x, int y) { if (x > y) x = y; }
inline void chmax(int &x, int y) { if (x < y) x = y; }
struct Tarjan {
	int Low[N], DFN[N], sta[N], Belong[N], num[N], scc; bool Insta[N];
	int d[N];
	void dfs(int u) {
		Low[u] = DFN[u] = ++*Low;
		sta[++*sta] = u;
		Insta[u] = 1;
		for (auto &it : G[u]) { 
			int v = it.fi;
			if (!DFN[v]) {
				dfs(v);
				Low[u] = min(Low[u], Low[v]);
			} else if (Insta[v])
				Low[u] = min(Low[u], DFN[v]); 
		}
		if (Low[u] == DFN[u]) {
			++scc;
			int v;
			do {
				v = sta[(*sta)--];
				Insta[v] = 0;
				Belong[v] = scc;
				++num[scc];
			} while (v != u); 
		}
	}
	void gao(int n) { 
		memset(DFN, 0, sizeof (DFN[0]) * (n + 10));
		memset(Insta, 0, sizeof (Insta[0]) * (n + 10));
		memset(num, 0, sizeof (num[0]) * (n + 10));
		scc = *sta = *Low = 0;
		for (int i = 1; i <= n; ++i) if (!DFN[i]) dfs(i);
	}
	void gogogo() {
		memset(d, 0, sizeof d);
		G1.clear(); G1.resize(scc + 1);
		for (int u = 1; u <= n; ++u) {
			for (auto &it : G[u]) { 
				int v = it.fi, w = it.se;
				if (vis[u] == 0 || vis[v] == 0) continue;
				if (Belong[u] == Belong[v]) {
					int id = Belong[u];
					chmin(g[id][0], w);
					chmax(g[id][1], w);
					chmin(f[id][0], w);
					chmax(f[id][1], w);
					chmax(f[id][2], g[id][1] - g[id][0]);
				} else {
					G1[Belong[u]].push_back(pII(Belong[v], w));
					++d[Belong[v]];
				}
			}
		}
		queue <int> que; 
		for (int i = 1; i <= scc; ++i) {
			if (d[i] == 0 && vis[i])
				que.push(i);
		}
		while (!que.empty()) {
			int u = que.front(); que.pop();
			for (auto &it : G1[u]) {
				int v = it.fi, w = it.se;
				chmin(f[v][0], f[u][0]);
				chmin(f[v][0], w);
				chmax(f[v][1], f[u][1]); 
				chmax(f[v][1], w);
				chmax(f[v][2], f[u][2]);
				chmax(f[v][2], max(max(w, g[v][1]) - f[u][0], f[u][1] - min(w, g[v][0])));
				chmax(f[v][2], w - g[v][0]);
				chmax(f[v][2], g[v][1] - w);
			//	chmax(f[v][2], w - f[v][0]);
			//	chmax(f[v][2], f[v][1] - w);
				if (--d[v] == 0)
					que.push(v);
			}	
		}
	//	for (int i = 1; i <= n; ++i) {
	//		dbg(i, f[Belong[i]][0], f[Belong[i]][1], f[Belong[i]][2]);
	//	}
	}
}tarjan;

void bfs() {
	memset(vis, 0, sizeof vis);
	queue <int> que;
	vis[1] = 1;
	que.push(1);
	while (!que.empty()) {
		int u = que.front(); que.pop();
		for (auto &it : G[u]) {
			int v = it.fi; 
			if (vis[v] == 0) {
				que.push(v);
				vis[v] = 1;
			}
		}
	}
}

int main() {
	while (scanf("%d%d%d", &n, &m, &q) != EOF) {
		for (int i = 1; i <= n; ++i) {
			f[i][0] = INF;
			f[i][1] = -INF;
			f[i][2] = 0;
			g[i][0] = INF;
			g[i][1] = -INF;
		}
		G.clear(); G.resize(n + 1); 
		for (int i = 1, u, v, w; i <= m; ++i) {
			scanf("%d%d%d", &u, &v, &w);
			G[u].push_back(pII(v, w)); 
		}
		bfs();
		tarjan.gao(n);
		tarjan.gogogo();
		for (int i = 1, x; i <= q; ++i) {  
			scanf("%d", &x); 
			if (vis[x] == 0 || (x == 1 && g[tarjan.Belong[x]][0] == INF)) puts("-1");
			else printf("%d\n", f[tarjan.Belong[x]][2]);
		}
	}
	return 0;
}
