#include <bits/stdc++.h>
using namespace std;
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
const int N = 5e5 + 10;
int n, m, q, h[N], ans[N];
struct E { 
	int u, v, w;
	bool operator < (const E &other) const {
		return w < other.w;
	}
}e[N];
struct W { 
	int v, x, k, id; 
	bool operator < (const W &other) const {
		return x < other.x;
	}
}w[N];

struct Hash {
	vector <int> a;
	int& operator[](int x) { return a[x]; }
	void init() { a.clear(); }
	void add(int x) { a.push_back(x); }
	void gao() { sort(a.begin(), a.end()); a.erase(unique(a.begin(), a.end()), a.end()); }
	int query(int x) { return lower_bound(a.begin(), a.end(), x) - a.begin() + 1; }	
}hs;

struct SEG {
	struct node {
		int ls, rs, v; 
		node() {}
		void init() { ls = rs = v = 0; }
	}t[N * 18];
	int tot;
	int newnode() { ++tot; t[tot].init(); return tot; }
	void Copy(int &x) { int tmp = newnode(); t[tmp] = t[x]; x = tmp; }
	void init() { tot = 0; }
	void pushup(int id) {
		int ls = t[id].ls, rs = t[id].rs;
		t[id].v = t[ls].v + t[rs].v;
	}
	void update(int &id, int l, int r, int pos, int v) {
		if (!id) id = newnode();
		if (l == r) {
			t[id].v += v;
			return;
		}
		int mid = (l + r) >> 1;
		if (pos <= mid) update(t[id].ls, l, mid, pos, v);
		else update(t[id].rs, mid + 1, r, pos, v);
		pushup(id);
	}
	void merge(int &x, int y, int l, int r) {
		if (!x || !y) { x |= y; return; }
		Copy(x);
		if (l == r) {
			t[x].v += t[y].v;
			return;
		}
		int mid = (l + r) >> 1;
		merge(t[x].ls, t[y].ls, l, mid);
		merge(t[x].rs, t[y].rs, mid + 1, r);
		pushup(x);
	}
	int query(int id, int l, int r, int k) {
		if (k <= 0) return -1;
		if (!id) return -1;
		if (l == r) return l;
		int mid = (l + r) >> 1;
		if (t[t[id].ls].v >= k) return query(t[id].ls, l, mid, k);
		else return query(t[id].rs, mid + 1, r, k - t[t[id].ls].v);
	}
}seg;

struct UFS {
	int fa[N], segrt[N];
	void init(int n) {
		for (int i = 1; i <= n; ++i) {
			fa[i] = 0;
			segrt[i] = 0;
			seg.update(segrt[i], 1, n, h[i], 1);
		}
	}
	int find(int x) { return fa[x] == 0 ? x : fa[x] = find(fa[x]); }
	void join(int x, int y) {
		int fx = find(x), fy = find(y);
		if (fx != fy) {
			fa[fx] = fy;
			seg.merge(segrt[fy], segrt[fx], 1, n); 
		}
	}
}ufs;

int main() {
	while (scanf("%d%d%d", &n, &m, &q) != EOF) {
		hs.init();
		for (int i = 1; i <= n; ++i) {
			scanf("%d", h + i);
			hs.add(h[i]);
		}
		hs.gao();
		for (int i = 1; i <= n; ++i) h[i] = hs.query(h[i]);
		for (int i = 1; i <= m; ++i) {
			scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
		}
		for (int i = 1; i <= q; ++i) {
			scanf("%d%d%d", &w[i].v, &w[i].x, &w[i].k);
			w[i].id = i;
		}
		sort(e + 1, e + 1 + m);
		sort(w + 1, w + 1 + q);
		ufs.init(n);
		for (int i = 1, pos = 0; i <= q; ++i) {
			while (pos < m && e[pos + 1].w <= w[i].x) ++pos, ufs.join(e[pos].u, e[pos].v);
			ans[w[i].id] = seg.query(ufs.segrt[ufs.find(w[i].v)], 1, n, seg.t[ufs.segrt[ufs.find(w[i].v)]].v - w[i].k + 1);
		}
		for (int i = 1; i <= q; ++i) {
			if (ans[i] != -1) ans[i] = hs[ans[i] - 1];
			printf("%d\n", ans[i]);
		}
	}
	return 0;
}
