#include <bits/stdc++.h>
using namespace std;

#define INF 0x3f3f3f3f
#define N 100010
#define pii pair <int, int>
#define fi first
#define se second
int cnt;
int n, m, q, u, v, res, kase; 
vector <vector<int>> G;
map <pii, int> mp;
int fa[N];
int find(int x) {
	return fa[x] == 0 ? x : fa[x] = find(fa[x]);
}
void join(int x, int y) {
	int fx = find(x), fy = find(y);
	if (fx != fy) {
		fa[fx] = fy;
	}
}
int used[N];
int BFS(int s, int t) {
	queue <pii> q;
	q.push(pii(s, 0));
	used[s] = kase;
	while (!q.empty()) {
		pii u = q.front(); q.pop();
		if (u.fi == t) {
			return u.se;
		}
		for (auto v : G[u.fi]) {
			if (used[v] != kase) {
				used[v] = kase;
				q.push(pii(v, u.se + 1));
			}
		}
	}
}

int limit;
int vis[N], dis[N];
void DFS(int u, int fa, int deep) {
	if (limit > 3000) return;
	++limit;
	for (auto v : G[u]) if (v != fa) {
		if (vis[v] < kase) {
			vis[v] = kase;
			dis[v] = deep;
		} else if (dis[v] > deep){
			dis[v] = min(dis[v], deep);
		} else {
			continue;
		}
		DFS(v, u, deep + 1);  
	}
}

void DFS2(int u, int fa, int deep) {
	if (limit > 3000) return;
	++limit;
	if (vis[u] == kase) {
		res = min(res, deep + dis[u]);
	}
	if (deep >= res) return;
	for (auto v : G[u]) if (v != fa) {
		DFS2(v, u, deep + 1);
	}
}


int work(int s, int t) {
	res = INF; vis[s] = kase; dis[s] = 0;
	limit = 0; DFS(s, s, 0);
	limit = 0; DFS2(t, t, 1);
	if (res == INF) {
		res = BFS(s, t);
	}
	return res;
}
void read(int &x) {
	x = 0; char ch;
	while (!isdigit(ch = getchar()));
	while (isdigit(ch)) {
		x = x * 10 + ch - '0';
		ch = getchar();
	}
}

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		cnt = 0;
		G.clear(); G.resize(n + 1);
		mp.clear();
		memset(fa, 0, sizeof fa);
		kase = 0;
		for (int i = 1; i <= m; ++i) {
			read(u); read(v);
			G[u].push_back(v);  
			G[v].push_back(u); 
			join(u, v);
		}
	//	int cnt = 0;
	//	for (int i = 1; i <= n; ++i) {
	//		cout << i << " " << G[i].size() << "\n";
	//		cnt += (G[i].size() >= 10);
	//	}
	//	cout << "cnt: " << cnt << endl;
		scanf("%d", &q);
		while (q--) {
			++kase;
			read(u); read(v);
			if (u == v) {
				puts("0");
			} else if (find(u) != find(v)) {
				puts("-1");
			} else {
				if (u > v) swap(u, v);
				if (mp.find(pii(u, v)) == mp.end()) {
					mp[pii(u, v)] = work(u, v);
				}
				printf("%d\n", mp[pii(u, v)]);
			}
		}
		//cout << "cnt: " << cnt << endl;
	}
	return 0;
}
