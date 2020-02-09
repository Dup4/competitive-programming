#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pII = pair<int, int>;
#define fi first
#define se second
const int N = 1e5 + 10;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
int n;
struct E { int to, nx, w, vis; }e[N << 2]; int h[N], tot;
inline void add(int u, int v, int w) {
	e[tot] = {v, h[u], w, 0}; h[u] = tot++;
	e[tot] = {u, h[v], w, 0}; h[v] = tot++;
}

int id(int i, int j) {
	return (i - 1) * n + j; 
}

pII fid(int x) {
	--x; 
	return pII(x / n + 1, x % n + 1);  
}

struct node {
	int to, pre; ll w; 
	node() {}
	node (int to, int pre, ll w) : to(to), pre(pre), w(w) {}
	bool operator < (const node &other) const {
		return w > other.w; 
	}
};

ll sum, dist[N];
int used[N], pre[N];
void Dijkstra() {
	for (int i = 1; i <= n * n; ++i) {
		dist[i] = INFLL;
		used[i] = 0;
		pre[i] = i; 
	}
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
				for (int i = h[u]; i != -1; i = e[i].nx) {
					int v = e[i].to;
					if (v == pre[u]) {
						e[i].vis = 1;
						e[i ^ 1].vis = 1;
						break;
					}
				}
				u = pre[u]; 
			}
		}
		for (int i = h[u]; i != -1; i = e[i].nx) {
			int v = e[i].to, w = e[i].w;
			if (!used[v] && dist[v] > dist[u] + w) {
				dist[v] = dist[u] + w;
				pq.push(node(v, u, dist[v]));
			}
		}
	}
}

vector <int> res;
void DFS(int u) {
	for (int &i = h[u]; i != -1; i = e[i].nx) {
		if (e[i].vis == 0) {
			int v = e[i].to;
			e[i].vis = 1;
			e[i ^ 1].vis = 1;
			DFS(v);
			res.push_back(v);
		}
		if (i == -1) break;
	}
}

int main() {
	int _T; scanf("%d", &_T);
	while (_T--) {
		scanf("%d", &n); 
		tot = 0;
		memset(h, -1, sizeof h);
		sum = 0;
		res.clear();
		for (int i = 1, w; i < n; ++i) {
			for (int j = 1; j <= i; ++j) {
				scanf("%d", &w);
				add(id(i, j), id(i + 1, j), w);
				sum += w; 
			} 
		}
		for (int i = 1, w; i < n; ++i) {
			for (int j = 1; j <= i; ++j) {
				scanf("%d", &w);
				add(id(i, j), id(i + 1, j + 1), w);
				sum += w;
			}
		}
		for (int i = 1, w; i < n; ++i) {
			for (int j = 1; j <= i; ++j) {
				scanf("%d", &w);
				add(id(i + 1, j), id(i + 1, j + 1), w);
				sum += w; 
			}
		}
		Dijkstra();
		DFS(1);
		res.push_back(1);
		reverse(res.begin(), res.end());
		printf("%lld\n", sum);
		printf("%d\n", (int)res.size());
		for (int i = 0, sze = (int)res.size(); i < sze; ++i) {
			pII cor = fid(res[i]);
			printf("%d %d%c", cor.fi, cor.se, " \n"[i == sze - 1]);
		}
	}
	return 0;
}
