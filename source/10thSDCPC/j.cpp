#include <bits/stdc++.h>
using namespace std;

#define N 90010
#define ll long long
#define INFLL 0x3f3f3f3f3f3f3f3f
#define pii pair <int, int>
#define fi first
#define se second
int n;
struct Graph {
	struct node {
		int to, nx, w, sta; 
		node () {}
		node (int to, int nx, int w) : to(to), nx(nx), w(w) {
			sta = 1;
		}
	}a[N << 2];
	int head[N], pos;
	void init(int n) {
		for (int i = 0; i <= n; ++i) {
			head[i] = 0;
		}
		pos = 0;
	}
	void add(int u, int v, int w) {
		a[++pos] = node(v, head[u], w); head[u] = pos;
		a[++pos] = node(u, head[v], w); head[v] = pos;
	}
}G;   
#define erp(u) for (int it = G.head[u], v = G.a[it].to, w = G.a[it].w, &sta = G.a[it].sta; it; it = G.a[it].nx, v = G.a[it].to, w = G.a[it].w, sta = G.a[it].sta)  
int id(int i, int j) {
	return (i - 1) * n + j;
}
pii fid(int x) {
	return pii(x / n + 1, x % n); 
}

struct node {
	int to, pre; ll w; 
	node() {}
	node (int to, int pre, ll w) : to(to), pre(pre), w(w) {}
	bool operator < (const node &other) const {
		return w > other.w; 
	}
};
ll sum;
ll dist[N];
int used[N];
int pre[N];
void Dijkstra() {
	for (int i = 1; i <= n * n; ++i) {
		dist[i] = INFLL;
		used[i] = 0;
		pre[i] = i; 
	}
	pre[1] = -1;
	dist[1] = 0;
	priority_queue <node> pq;
	pq.push(node(1, -1, 0));
	while (!pq.empty()) {
		int u = pq.top().to, fa = pq.top().pre; pq.pop();
		if (used[u]) {
			continue;
		}
		pre[u] = fa;
		used[u] = 1;
		if (u == n * n) {
			sum -= dist[u];
			while (pre[u] != -1) {
				erp(u) if (v == pre[u]) {
					sta = 0;
					break;
				}
				erp(pre[u]) if (v == u) {
					sta = 0;
					break;
				}
				u = pre[u]; 
			}
		}
		erp(u) if (!used[v] && dist[v] > dist[u] + w) {
			dist[v] = dist[u] + w;
			pq.push(node(v, u, dist[v]));
		}
	}
}
vector <int> res;
void DFS(int u) {
	erp(u) if (sta) { 
		sta = 0;
		printf("%d %d\n", u, v);
		for (int it2 = G.head[v], vv = G.a[it2].to, &staa = G.a[it2].sta; it2; it2 = G.a[it2].nx, vv = G.a[it2].to, staa = G.a[it2].sta) if (vv == u) {
			staa = 0;
			break;
		}
		DFS(v);
		res.push_back(v);
	}
}

void init() {
	G.init(n * n + 10);
	sum = 0;
	res.clear();
}
int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n); init();
		for (int i = 1, w; i < n; ++i) {
			for (int j = 1; j <= i; ++j) {
				scanf("%d", &w);
				G.add(id(i, j), id(i + 1, j), w);
				sum += w; 
			} 
		}
		for (int i = 1, w; i < n; ++i) {
			for (int j = 1; j <= i; ++j) {
				scanf("%d", &w);
				G.add(id(i, j), id(i + 1, j + 1), w);
				sum += w;
			}
		}
		for (int i = 1, w; i < n; ++i) {
			for (int j = 1; j <= i; ++j) {
				scanf("%d", &w);
				G.add(id(i + 1, j), id(i + 1, j + 1), w);
				sum += w; 
			}
		}
		Dijkstra();
		DFS(1);
		res.push_back(1);      	
		printf("%lld\n", sum);
		for (int i = 0, sze = (int)res.size(); i < sze; ++i) {
			pii cor = fid(res[i]);
			printf("%d %d%c", cor.fi, cor.se, " \n"[i == sze - 1]);
		}
	}
	return 0;
}
