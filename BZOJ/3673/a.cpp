#include <bits/stdc++.h>
using namespace std;

#define N 20010
#define pii pair <int, int>
#define fi first
#define se second
int n, q;
struct SEG {
	struct node {
		int ls, rs;
		int fa, sze;
		node () {
			ls = rs = 0; 
			fa = 0;
			sze = 1;
		}
	}t[N * 50]; 
	int rt[N], tot;
	void init() {
		tot = 0;
		memset(rt, 0, sizeof rt);
		t[0] = node();
	}
	void build(int &id, int l, int r) { 
		if (id == 0) { 
			id = ++tot;
		}
		if (l == r) {
			t[id] = node();
			t[id].fa = l;
			return;
		}
		int mid = (l + r) >> 1;
		build(t[id].ls, l, mid);
		build(t[id].rs, mid + 1, r);  
	}
	void update(int &now, int pre, int l, int r, int pos, int fa) {  
		now = ++tot;
		if (l == r) {
			t[now] = node();
			t[now].fa = fa;
			t[now].sze = t[pre].sze;
			return;	
		}
		t[now].ls = t[pre].ls;
		t[now].rs = t[pre].rs;
		int mid = (l + r) >> 1;
		if (pos <= mid) {
			update(t[now].ls, now, l, mid, pos, fa);
		} else {
			update(t[now].rs, now, mid + 1, r, pos, fa); 
		}
	}
	void add(int &now, int pre, int l, int r, int pos, int sze) {
		now = ++tot;
		if (l == r) {
			t[now] = node();
			t[now].fa = t[pre].fa;
			t[now].sze = t[pre].sze + sze;
			return;
		}
		t[now].ls = t[pre].ls;
		t[now].rs = t[pre].rs;
		int mid = (l + r) >> 1;
		if (pos <= mid) {
			add(t[now].ls, now, l, mid, pos, sze);
		} else {
			add(t[now].rs, now, mid + 1, r, pos, sze);
		}
	}
	pii query(int now, int l, int r, int pos) {
		if (l == r) {
			return pii(t[now].fa, t[now].sze);
		}
		int mid = (l + r) >> 1;
		if (pos <= mid) {
			return query(t[now].ls, l, mid, pos);
		} else {
			return query(t[now].rs, mid + 1, r, pos);
		}
	}
}seg; 

pii find(int k, int x) {
	pii pre = seg.query(seg.rt[k], 1, n, x);
	if (pre.fi == x) {
		return pre;  
	} else {
		return find(k, pre.fi); 
	}
}
void join(int k, int x, int y) {
	pii fx = find(k, x), fy = find(k, y);
	if (fx.fi != fy.fi) {  
		if (fx.se > fy.se) {
			swap(fx, fy);
		}
		seg.update(seg.rt[k], seg.rt[k], 1, n, fx.fi, fy.fi);
		seg.add(seg.rt[k], seg.rt[k], 1, n, fy.fi, fx.se);
	}
}
bool same(int k, int x, int y) {
	pii fx = find(k, x), fy = find(k, y);
	return fx.fi == fy.fi;
}
int main() {
	while (scanf("%d%d", &n, &q) != EOF) {
		seg.init();
		seg.build(seg.rt[0], 1, n);
		int op, x, y, k;
		for (int i = 1; i <= q; ++i) {
			scanf("%d", &op);
			seg.rt[i] = seg.rt[i - 1];
			switch(op) {
				case 1 :
					scanf("%d%d", &x, &y);
					join(i, x, y);
					break;
				case 2 :
					scanf("%d", &k);
					seg.rt[i] = seg.rt[k];
					break;
				case 3 :
					scanf("%d%d", &x, &y);
					puts(same(i, x, y) ? "1" : "0");
					break;
				default :
					assert(0);
			}
		}
	}
	return 0;
}
