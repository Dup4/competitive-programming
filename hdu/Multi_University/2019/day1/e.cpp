#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 10010
#define pii pair <int, int>
#define fi first
#define se second
int n, m, t;
int e[N][3]; 
map <pii, ll> mp[N];
struct node {
	int u, v, w;
	ll cost;
	node () {}
	node (int u, int v, int w, ll cost) : u(u), v(v), w(w), id(id) {}
	bool operator < (const node &other) const {
		return w > other.w; 
	}
};
vector <multiet<pii>> G;


void Dijkstra() {
	
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		t = 0;
		G.clear(); G.resize(n + 1);
	    for (int i = 1; i <= n; ++i) mp[i].clear();	
		for (int i = 1; i <= m; ++i) {
			int &u = e[i][0], &v = e[i][1], &w = e[i][2]; 
			scanf("%d%d%d", &u, &v, &w);
		    if (mp[u].find(pii(v, w)) == mp[u].end()) {
				mp[u][pii(v, w)] = w;
				G[u].insert(node(u, v, w, w));
			} else {
				G[u].erase(node(u, v, w, mp[u][pii(v, w)]));
				mp[u][pii(v, w)] += w;
				G[u].insert(node(u, v, w, mp[u][pii(v, w)]));
			}
		}
		ll last = INF; 
		while (1) {
	
		}
	}
	return 0;
}
