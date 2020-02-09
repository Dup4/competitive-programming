#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
vector <int> num[N], G[N];
int n;
int a[N], rt[N], ans[N];

void Init() {
	for (int i = 1; i <= 100000; ++i) 
		for (int j = i; j <= 100000; j += i)
			num[j].push_back(i);
}

struct SEG {
	struct node {
		int ls, rs, v;
		node() {};
		void init() { ls = rs = v = 0; }
	}t[N * 400];
	int tot;
	int newnode() { ++tot; t[tot].init(); return tot; }
	void init() { tot = 0; }
	void pushup(int id) {
		int ls = t[id].ls, rs = t[id].rs;
		t[id].v = max(t[ls].v, t[rs].v);
	}
	void update(int &id, int l, int r, int pos) {
		if (!id) id = newnode();
		if (l == r) { t[id].v = pos; return; }
		int mid = (l + r) >> 1;
		if (pos <= mid) update(t[id].ls, l, mid, pos);
		else update(t[id].rs, mid + 1, r, pos);
		pushup(id);
	}
	void merge(int &x, int y, int l, int r, int &ans) { 
		if (!x || !y) { x |= y; return; }
		if (l == r) {
			ans = max(ans, l); 
			return;
		}
		int mid = (l + r) >> 1;
		merge(t[x].ls, t[y].ls, l, mid, ans);
		merge(t[x].rs, t[y].rs, mid + 1, r, ans); 
		pushup(x);
	}
}seg;

void DFS(int u) {
	ans[u] = -1;
	for (auto v : G[u]) {
		DFS(v);
		seg.merge(rt[u], rt[v], 1, 100000, ans[u]); 
	}
}

int main() {
	Init();
	while (scanf("%d", &n) != EOF) {
		seg.init();
		for (int i = 2, u; i <= n; ++i) {
			scanf("%d", &u);
			G[u].push_back(i);
		}
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		for (int i = 1; i <= n; ++i) 
			for (auto it : num[a[i]]) 
				seg.update(rt[i], 1, 100000, it);  
		DFS(1);
		for (int i = 1; i <= n; ++i) printf("%d\n", ans[i]);
	}
	return 0;
}
