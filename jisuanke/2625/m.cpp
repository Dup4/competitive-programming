#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 1e5 + 10;

struct node {
	int pos, step;
	node(){}
	node(int pos, int step): pos(pos), step(step){}
};

struct Edge {
	int to, nxt, w;
	Edge() {}
	Edge(int to, int nxt, int w): to(to), nxt(nxt), w(w) {}
}edge[maxn << 1];

int n, m;
ll c, d, e;
int head[maxn], tot;
int vis[maxn];

void Init() {
	tot = 0;
	memset(head, -1, sizeof head);
}

void addedge(int u,int v, int w) {
	edge[tot] = Edge(v, head[u], w); head[u] = tot++;
	edge[tot] = Edge(u, head[v], w); head[v] = tot++;
}

bool BFS(ll D, ll E) {
	for (int i = 1; i <= n; ++i) {
		vis[i] = 0;
	}
	queue<node>q;
	q.push(node(1, 0));
	vis[1] = 1;
	while(!q.empty()) {
		node st = q.front();
		q.pop();
		int u = st.pos;
		if (st.step >= E) {
			continue;
		}
		if (st.pos == n) {
			return true;
		}
		for (int i = head[u]; ~i; i = edge[i].nxt) {
			int v = edge[i].to;
			int w = edge[i].w;
			if (w > D) continue;
			if (vis[v]) continue;
			if (v == n) return true;
			vis[v] = 1;
			q.push(node(v, st.step + 1));
		}
	}
	return false;
} 

int main() {
	while(~scanf("%d %d", &n, &m)) {
		scanf("%lld %lld %lld", &c, &d ,&e);
		Init();
		for (int i = 1, u, v, w; i <= m; ++i) {
			scanf("%d %d %d" ,&u, &v ,&w);
			addedge(u, v, w);
		}
		ll l = 0, r = 1e9, res = 0;
		while(r - l >= 0) {
			ll mid = (l + r) >> 1;
			if (BFS(d * mid, e * mid)) {
				r = mid - 1;
				res = mid;
			} else {
				l = mid + 1;
			}
		}
		printf("%lld\n", res * c);
	}
	return 0;
}
