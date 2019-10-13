#include <bits/stdc++.h>
using namespace std;

const int N = 4e6 + 10;
int n, m, p, id;
struct Edge { int v, nx, w; }e[N]; int h[N]; 
inline void addedge(int u, int v, int w) { e[++*h] = {v, h[u], w}; h[u] = *h; }
struct SEG {
	struct node {
		int ls, rs;
		node() { ls = rs = 0; }
	}t[N << 4];
	int rt_in, rt_out, tot;
	inline void init() { rt_in = rt_out = tot = 0; }
	inline int newnode() { ++tot; t[tot] = node(); return tot; }
	void build(int &rt, int l, int r, int op) {
		rt = newnode();
		if (l == r) return;
		int mid = (l + r) >> 1;
		build(t[rt].ls, l, mid, op);
		build(t[rt].rs, mid + 1, r, op);
		//in_tree
		if (op == 1) {
			addedge(rt, t[rt].ls, 0);
			addedge(rt, t[rt].rs, 0);
		} else {
			addedge(t[rt].ls, rt, 0);
			addedge(t[rt].rs, rt, 0); 
		}
	}
	
}seg;

int main() {
	while (scanf("%d%d%d", &n, &m, &p) != EOF) {
		memset(h, 0, sizeof h);
		id = 0;
		
		
	}
	return 0;
}
