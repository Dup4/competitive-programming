#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
using namespace std;
using namespace __gnu_pbds;

#define ll long long
#define INFLL 0x3f3f3f3f3f3f3f3f
#define N 1000010
#define M 10000010
int n, m, T, rxa, rxc, rya, ryc, rp;
struct Graph {
	struct node {
		int to, nx, w;
		node() {}
		node (int to, int nx, int w) : to(to), nx(nx), w(w) {}
	}a[M];
	int head[N], pos;
	void init() {
		memset(head, -1, sizeof head);
		pos = 0;
	}
	void add(int u, int v, int w) {
		a[++pos] = node(v, head[u], w); head[u] = pos;
	}
}G;
#define erp(u) for (int it = G.head[u], v = G.a[it].to, w = G.a[it].w; it; it = G.a[it].nx, v = G.a[it].to, w = G.a[it].w)

struct node {
	int u; ll w;
	node() {}
	node (int u, ll w) : u(u), w(w) {}
	bool operator < (const node &other) const {
		return w > other.w;
	}
};
#define heap __gnu_pbds::priority_queue <node, less<node>, pairing_heap_tag>

ll dis[N]; bool used[N];
heap::point_iterator id[N]; 
void Dijkstra() {
	for (int i = 1; i <= n; ++i) {
		used[i] = 0;
		dis[i] = INFLL;
		id[i] = 0;
	}
	dis[1] = 0;
	heap pq;
	id[1] = pq.push(node(1, 0)); 
	while (!pq.empty()) {
		int u = pq.top().u; pq.pop();
		if (used[u]) continue;
		used[u] = 1;
		erp(u) if (dis[v] > dis[u] + w) {
			dis[v] = dis[u] + w;
			if (id[v] == 0) {
				id[v] = pq.push(node(v, dis[v]));
			} else {
				pq.modify(id[v], node(v, dis[v]));
			}
		}
	}
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
		scanf("%d%d%d%d%d%d", &T, &rxa, &rxc, &rya, &ryc, &rp);
		G.init();
		ll x = 0, y = 0, z = 0, a, b;
		for (int i = 1, a, b; i <= T; ++i) {
			x = (x * rxa + rxc) % rp;
			y = (y * rya + ryc) % rp;
			a = x % n + 1; b = y % n + 1;
			if (a > b) swap(a, b);
			G.add(a, b, 100000000 - 100 * a);
		}
		for (int i = 1, u, v, w; i <= m - T; ++i) {
			read(u); read(v); read(w);
			G.add(u, v, w);
		}
		Dijkstra();
		printf("%lld\n", dis[n]);
	}
	return 0;
}
