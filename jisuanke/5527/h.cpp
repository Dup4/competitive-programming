#include <bits/stdc++.h>
using namespace std;
using pII = pair<int, int>;
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0)
void err() { cout << "\033[39;0m" << endl; }
template <class T, class... Ts>
void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
#define fi first
#define se second
const int N = 5e4 + 10, INF = 0x3f3f3f3f;
int n, mx, my, s, id[N], d[N];
//0 two-way 1 one-way
vector <vector<pII>> G[3];
vector <vector<int>> po;
struct DSU {
	int fa[N];
	void init() { memset(fa, 0, sizeof fa); }
	int find(int x) {
		return fa[x] == 0 ? x : fa[x] = find(fa[x]);
	}
	void merge(int u, int v) {
		int fu = find(u), fv = find(v);
		if (fu != fv) {
			fa[fu] = fv;
		}
	}
}dsu;

struct node {
	int u, w;
	node() {}
	node(int u, int w) : u(u), w(w) {}
	bool operator < (const node &other) const {
		return w > other.w;
	}
};
int dis[N], used[N];
void Dijkstra(int S) {
	priority_queue <node> pq;
	pq.push(node(S, dis[S]));
	while (!pq.empty()) {
		int u = pq.top().u; pq.pop();
		for (auto &it : G[0][u]) { 
			int v = it.fi, w = it.se;
			if (dis[v] > dis[u] + w) {
				dis[v] = dis[u] + w;
				pq.push(node(v, dis[v]));
			}	
		}
	}
}

void Topo() {
	queue <int> que;
	for (int i = 1; i <= *id; ++i) {
		if (d[i] == 0) {
			que.push(i);
		}
	}	
	while (!que.empty()) {
		int u = que.front(); que.pop();
		sort(po[u].begin(), po[u].end(), [&](int a, int b) { return dis[a] < dis[b]; });
		for (auto &it : po[u]) {
			Dijkstra(it);
			for (auto &it2 : G[1][it]) {
				int v = it2.fi, w = it2.se;
				if (dis[it] < INF) {
					dis[v] = min(dis[v], dis[it] + w);
				}
			}
		}	
		for (auto &it : G[2][u]) {
			int v = it.fi;
			if (--d[v] == 0) {
				que.push(v);
			}
		}
	}
}

int main() {
	while (scanf("%d%d%d%d", &n, &mx, &my, &s) != EOF) {
		for (int i = 1; i <= n; ++i) {
			dis[i] = INF;
		}
		dis[s] = 0;
		*id = 0;
		G[0].clear(); G[1].clear();
		G[0].resize(n + 1); G[1].resize(n + 1);
		for (int i = 1, u, v, w; i <= mx; ++i) {
			scanf("%d%d%d", &u, &v, &w);
			G[0][u].push_back(pII(v, w));
			G[0][v].push_back(pII(u, w));
		}
		for (int i = 1, u, v, w; i <= my; ++i) {
			scanf("%d%d%d", &u, &v, &w);
			G[1][u].push_back(pII(v, w));
		}
		dsu.init();
		for (int u = 1; u <= n; ++u) {
			for (auto &it : G[0][u]) {
				int v = it.fi;
				dsu.merge(u, v);
			}
		}
		for (int u = 1; u <= n; ++u) {
			if (dsu.fa[u] == 0)
				id[u] = ++*id;
		}
		for (int u = 1; u <= n; ++u) {
			if (dsu.fa[u]) {
				id[u] = id[dsu.find(u)];
			}
		}
	//	for (int i = 1; i <= n; ++i)
	//		dbg(i, id[i]); 
		po.clear(); po.resize(*id + 10);
		G[2].clear(); G[2].resize(*id + 10);
		memset(d, 0, sizeof d);
		for (int u = 1; u <= n; ++u) {
		    po[id[u]].push_back(u);	
			for (auto &it : G[1][u]) { 
				int v = it.fi;
				if (id[u] != id[v]) {
					G[2][id[u]].push_back(pII(id[v], v));
					++d[id[v]];
				}
			}
		}
		Topo();
		for (int i = 1; i <= n; ++i) {
			if (dis[i] >= INF) puts("NO PATH");
			else printf("%d\n", dis[i]);
		}
		
	}
	return 0;
}
