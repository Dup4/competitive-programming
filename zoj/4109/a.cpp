#include <bits/stdc++.h>
using namespace std;

#define N 1000010
int n, m;
vector < vector <int> > G;
priority_queue <int, vector <int>, greater <int> > pq;
vector <int> res_ord;
int used[N];
void Toposort() {
	while (!pq.empty()) {
		int u = pq.top(); pq.pop();
		res_ord.push_back(u);
		for (auto v : G[u]) if (!used[v]) {
			used[v] = 1;
			pq.push(v);
		}
	}
}

struct UF {
	struct node {
		int fa, Ra, x;
		node() {}
		node(int fa, int Ra, int x) : fa(fa), Ra(Ra), x(x) {}
	}t[N];
	void init(int n) {
		for (int i = 1; i <= n; ++i) {
			t[i] = node(i, 1, i);		
		}
	}
	int find(int x) {
		return t[x].fa == x ? x : t[x].fa = find(t[x].fa);
	}
	void merge(int x, int y) {
		x = find(x), y = find(y);
		if (x != y) {
			if (t[x].Ra > t[y].Ra) { 
				swap(x, y);
			}
			t[x].fa = y;
			t[y].x = min(t[y].x, t[x].x);
			t[y].Ra += t[x].Ra;
		}
	}
}uf;

void init() {
	G.clear();
	G.resize(n + 1);
	uf.init(n);
	while (!pq.empty()) pq.pop();
	res_ord.clear();
	for (int i = 1; i <= n; ++i) {
		used[i] = 0;
	}
}
int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		init();
		for (int i = 1, u, v; i <= m; ++i) {
			scanf("%d%d", &u, &v);
			G[u].push_back(v);
			G[v].push_back(u);
			uf.merge(u, v);
		}
		int res = 0;
		for (int i = 1; i <= n; ++i) {
			if (uf.find(i) == i) {
				++res;
				used[uf.t[i].x] = 1;
				pq.push(uf.t[i].x);
			}
		}
		Toposort();
		printf("%d\n", res);
		for (int i = 0; i < n; ++i) {
			printf("%d%c", res_ord[i], " \n"[i == n - 1]);
		}
	}
	return 0;
}
