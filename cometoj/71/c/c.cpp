#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pII = pair<int, int>;
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
#define fi first
#define se second
const int N = 1e6 + 10, INF = 0x3f3f3f3f;
int m, n1, n2, s, t1, t2;
vector <vector<int>> tt;
vector <vector<pII>> G;
inline int id(int x, int y) { return (x - 1) * m + y; }
inline void addedge(int u, int v, int w) { G[u].push_back(pII(v, w)); }

struct node {
	int u,  w;
	node() {}
	node (int u, int w) : u(u), w(w) {}
	bool operator < (const node &other) const {
		return w > other.w;
	}
};

int dis[N], used[N]; 
void Dijkstra() {
	priority_queue <node> pq;
	for (int i = 0; i <= m * (n1 + n2); ++i) {
		dis[i] = INF;
		used[i] = 0;
	}
	dis[0] = 0;
	pq.push(node(0, dis[0]));
	while (!pq.empty()) {
		int u = pq.top().u; pq.pop();
		if (used[u]) continue;
		used[u] = 1;
		for (auto &it : G[u]) {
			int v = it.fi, w = it.se;
			if (used[v] == 0 && dis[v] > dis[u] + w) {
				dis[v] = dis[u] + w;
				pq.push(node(v, dis[v]));
			}
		}
	}
}

int main() {
	int _T; scanf("%d", &_T);
	while (_T--) {
		scanf("%d%d%d%d%d%d", &m, &n1, &n2, &s, &t1, &t2);
		tt.clear(); tt.resize(n1 + n2 + 10);
		G.clear(); G.resize(m * (n1 + n2) + 10);
		for (int i = 1; i <= m; ++i) {
			vector <pII> tmp;
			for (int j = 1, x; j <= n1 + n2; ++j) {
				scanf("%d", &x);
				tmp.push_back(pII(x, j));
				tt[j].push_back(x);
			}
			sort(tmp.begin(), tmp.end(), [&](pII x, pII y) { return x.fi < y.fi; }); 
			for (int j = 1; j < n1 + n2; ++j) {
				addedge(id(tmp[j - 1].se, i), id(tmp[j].se, i), tmp[j].fi - tmp[j - 1].fi);
				if (tmp[j].fi == tmp[j - 1].fi) {
					addedge(id(tmp[j].se, i), id(tmp[j - 1].se, i), 0);
				}
			}	
			if (s == i) {
				for (int j = 0; j < n1 + n2; ++j) {
					if (tmp[j].fi >= t1) {
						addedge(0, id(tmp[j].se, i), tmp[j].fi - t1); 
						break;
					}
				}
			}
		}
		for (int i = 1; i <= n1; ++i) {
			for (int j = 1; j < m; ++j) {
				addedge(id(i, j), id(i, j + 1), 0);
			}
		}
		for (int i = n1 + 1; i <= n1 + n2; ++i) {
			for (int j = m - 2; j >= 0; --j) {
				addedge(id(i, j + 2), id(i, j + 1), 0);
			}
		}
		Dijkstra();
		int res = t2 - t1;
		for (int i = 1; i <= n1 + n2; ++i) {
			if (t2 >= tt[i][s - 1]) {
				res = min(res, t2 - tt[i][s - 1] + dis[id(i, s)]); 
			} 
		}
		printf("%d\n", res);
	}
	return 0;
}
