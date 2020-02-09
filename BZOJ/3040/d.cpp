#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define INFLL 0x3f3f3f3f3f3f3f3f
const int N = 1e6 + 10, M = 1e7 + 10; 
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
		a[pos] = node(v, head[u], w); head[u] = pos++; 
	}
}G;
#define erp(u) for (int it = G.head[u], v = G.a[it].to, w = G.a[it].w; ~it; it = G.a[it].nx, v = G.a[it].to, w = G.a[it].w)

struct Pairing_Heap {
	//内存池
	struct Stack {
		int S[N], s, k;
		Stack() {}
		void init() { s = k = 0; }
		int get() {
			return s ? S[s--] : ++k;
		}
		void save(int index) {
			S[++s] = index;
		}
	}Node; 
	//节点属性
	struct node {
		int fa, id; ll val;
		node() { fa = -1; }
		node(int fa, int id, ll val) : fa(fa), id(id), val(val) {}
		//小根堆
		bool operator < (const node &other) const {
			return val < other.val; 
		}
	}a[N];
	//链式前向星 
	struct Graph {
		struct node {
			int to, nx;
			int *pre; 
			node() { pre = NULL; }
			node (int to, int nx, int *pre) : to(to), nx(nx), pre(pre) {}
		}a[N];
		int head[N]; 
		void init() { 
			memset(head, -1, sizeof head); 
		}
		void savePoint(int u) { 
			head[u] = -1;
		}
		void add(int u, int v, int index) {
		    if (a[index].pre != NULL) {
				a[a[index].nx].pre = a[index].pre;
				*a[index].pre = a[index].nx; 
			}	
			if (head[u] != -1) a[head[u]].pre = &a[index].nx; 
		    a[index] = node(v, head[u], &head[u]); head[u] = index;
		}
	}G;
	int root; 
	void init() {
		root = 0;
		G.init();
		Node.init();
	}
	int merge(int u, int v) {
		if (a[v] < a[u]) swap(u, v);
		a[v].fa = u;
		G.add(u, v, v); 	
		return u;
	}
	int push(int id, ll val) {
		int u = Node.get();
		a[u] = node(-1, id, val);
		root = root ? merge(root, u) : u;
		return u;
	}
	int top() {
		return a[root].id;
	}
	void modify(int u, int id, ll val) {
		a[u] = node(-1, id, val); 
		if (u != root) {
			root = merge(root, u);
		} 
	}
	void pop() {
		queue <int> que;
		for (int it = G.head[root], v = G.a[it].to; ~it; it = G.a[it].nx, v = G.a[it].to) {
			if (a[v].fa == root) {
				a[v].fa = -1; 
				que.push(v);
			}
		}
		G.savePoint(root); Node.save(root); root = 0;
		while (!que.empty()) {
			int u = que.front(); que.pop();
			if (que.empty()) {
				root = u;
				return;
			}
			int v = que.front(); que.pop();
			que.push(merge(u, v));
		}
	}
	bool empty() {
		return root == 0;
	}
}ph;

ll dis[N];
int id[N];
void Dijkstra() {
	for (int i = 2; i <= n; ++i) {
		dis[i] = INFLL;
		id[i] = 0;
	}
	ph.init();
	dis[1] = 0;
	id[1] = ph.push(1, 0); 
	while (!ph.empty()) {
		int u = ph.top(); ph.pop();
		erp(u) if (dis[v] > dis[u] + w) {
			dis[v] = dis[u] + w;
			if (id[v] == 0) {
				id[v] = ph.push(v, dis[v]);
			} else {
				ph.modify(id[v], v, dis[v]); 
			}
		}
	}
}

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		scanf("%d%d%d%d%d%d", &T, &rxa, &rxc, &rya, &ryc, &rp);
		G.init();
		ll x = 0, y = 0, a, b;
		for (int i = 1; i <= T; ++i) {
			x = (x * rxa + rxc) % rp;
			y = (y * rya + ryc) % rp;
			a = min(x % n + 1, y % n + 1);
			b = max(x % n + 1, y % n + 1);
			G.add(a, b, 100000000 - 100 * a);
		}
		for (int i = 1, u, v, w; i <= m - T; ++i) {
			scanf("%d%d%d", &u, &v, &w);
			G.add(u, v, w);
		}
		Dijkstra();
		printf("%lld\n", dis[n]);
	}
	return 0;
}
