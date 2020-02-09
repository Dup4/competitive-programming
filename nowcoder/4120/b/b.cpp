#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10;
int n, m, e[N][2], rt[N], ans[N];

struct SEG {
	struct node {
		int ls, rs, sum;
		node() { ls = rs = sum = 0; }
		node(int ls, int rs, int sum) : ls(ls), rs(rs), sum(sum) {}
	}t[N * 43]; 
	int tot;
	int newnode() { ++tot; t[tot] = node(); return tot; } 
	void Copy(int &x) { int tmp = newnode(); t[tmp] = t[x]; x = tmp; }
	void init() { tot = 0; newnode(); } 
	void up(int id) {
		int ls = t[id].ls, rs = t[id].rs, &sum = t[id].sum;
		sum = 0;
		if (ls) sum += t[ls].sum;
		if (rs) sum += t[rs].sum;
	}
	void update(int &now, int l, int r, int pos) {
		if (!now) now = newnode();
		if (l == r) {
			++t[now].sum;
			return;
		}
		int mid = (l + r) >> 1;
		if (pos <= mid) update(t[now].ls, l, mid, pos);
		else update(t[now].rs, mid + 1, r, pos);
		up(now);
	}
	void merge(int &x, int y, int l, int r) {
		if (!x && !y) return 0;
		if (!x) {
			
		}
		if (!x || !y) {x |= y; return; }
		Copy(x); 
		if (l == r) {
			++ans[l]; 
			t[x].sum = t[x].sum | t[y].sum; 
			return;
		}
		int mid = (l + r) >> 1;
		merge(t[x].ls, t[y].ls, l, mid);
		merge(t[x].rs, t[y].rs, mid + 1, r);
		up(x);
	}
    void merge1(int &x, int y, int l, int r) {
		if (!x || !y) { x |= y; return; }
		Copy(x); 
		if (l == r) {
			t[x].sum += t[y].sum;
			return;
		}
		int mid = (l + r) >> 1;
		merge1(t[x].ls, t[y].ls, l, mid);
		merge1(t[x].rs, t[y].rs, mid + 1, r);
		up(x);
	}	
	int query(int id, int l, int r, int ql, int qr) {
		if (!id || ql > qr) return 0;
		if (l >= ql && r <= qr) return t[id].sum;
		int mid = (l + r) >> 1;
		int res = 0;
		if (ql <= mid) res += query(t[id].ls, l, mid, ql, qr);
	    if (qr > mid) res += query(t[id].rs, mid + 1, r, ql, qr);
		return res;	
	}
}seg;

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		for (int i = 1; i < n; ++i) scanf("%d%d", e[i], e[i] + 1);
		seg.init();
		for (int i = 1; i <= n; ++i) { 
			ans[i] = 1; 
			rt[i] = 0; seg.update(rt[i], 1, n, i);
		}
		for (int i = 1, p; i <= m; ++i) {
			scanf("%d", &p);
			int u = e[p][0], v = e[p][1];
			seg.merge(rt[u], rt[v], 1, n);
			rt[v] = rt[u];
		}	
	//	for (int i = 2; i <= n; ++i) {
	//		seg.merge1(rt[1], rt[i], 1, n);
	//	}
		for (int i = 1; i <= n; ++i)
			printf("%d%c", ans[i], " \n"[i == n]);
	}
	return 0;
}
