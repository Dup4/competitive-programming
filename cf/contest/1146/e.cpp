#include <bits/stdc++.h>
using namespace std;

#define N 200010
#define D 100005
int n, q, a[N];

struct SEG {
	struct node {
		int x, lazy[2];   
		node () {
			x = 1;
			lazy[0] = 0;
			lazy[1] = 1; 
		}
		void add1(int v) {
			lazy[1] = 1;
			lazy[0] = v;
			x = v;
		}
		void add2(int v) {
			x *= v; 
			if (lazy[0] != 0) {
				lazy[0] *= v;
			} else {
				lazy[1] *= v;
			}
		}
	}t[N << 2];
	void build(int id, int l,int r) {
		if (l == r) {
			t[id] = node();
			return;
		}
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
	}
	void pushdown(int id) {
		if (t[id].lazy[1] != 1) {
			t[id << 1].add2(t[id].lazy[1]);
			t[id << 1 | 1].add2(t[id].lazy[1]);
			t[id].lazy[1] = 1;
		}
		if (t[id].lazy[0] != 0) {
			t[id << 1].add1(t[id].lazy[0]);
			t[id << 1 | 1].add1(t[id].lazy[0]);
			t[id].lazy[0] = 0;
		}
	}
	void update1(int id, int l ,int r, int ql, int qr, int v) {
		if (ql > qr) {
			return;
		}
		if (l >= ql && r <= qr) {
			t[id].add1(v);
			return;
		}
		int mid = (l + r) >> 1;
		pushdown(id);
		if (ql <= mid) update1(id << 1, l, mid, ql, qr, v);
		if (qr > mid) update1(id << 1 | 1, mid + 1, r, ql, qr, v);
	}
	void update2(int id, int l, int r, int ql, int qr, int v) {
		if (ql > qr) {
			return;
		}
		if (l >= ql && r <= qr) {
			t[id].add2(v);
			return;
		}
		int mid = (l + r) >> 1;
		pushdown(id);
		if (ql <= mid) update2(id << 1, l, mid, ql, qr, v);
		if (qr > mid) update2(id << 1 | 1, mid + 1, r, ql, qr, v);
	}
	int query(int id, int l, int r, int pos) {
		if (l == r) {
			return t[id].x;
		}
		int mid = (l + r) >> 1;
		pushdown(id);
		if (pos <= mid) return query(id << 1, l, mid, pos);
		else return query(id << 1 | 1, mid + 1, r, pos);
	}
}seg;

int main() {
	while (scanf("%d%d", &n, &q) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
		}
		seg.build(1, 1, 2 * D);
		char op[10]; int x;
		while (q--) {
			scanf("%s%d", op, &x);
			switch(op[0]) {
				case '>' :
					if (x < 0) {
						seg.update2(1, 1, 2 * D, x + 1 + D, -x - 1 + D, -1);
						seg.update1(1, 1, 2 * D, -100000 + D, x + D, 1);
						seg.update1(1, 1, 2 * D, -x + D, 100000 + D, -1);
					} else {
						seg.update1(1, 1, 2 * D, x + 1 + D, 100000 + D, -1);
						seg.update1(1, 1, 2 * D, -100000 + D, -x - 1 + D, 1);
					}
					break;
				case '<' :
					if (x > 0) {
						seg.update2(1, 1, 2 * D, -x + 1 + D, x - 1 + D, -1);
						seg.update1(1, 1, 2 * D, x + D, 100000 + D, 1);
						seg.update1(1, 1, 2 * D,  -100000 + D, -x + D, -1);	
					} else {
						seg.update1(1, 1, 2 * D, -100000 + D, x - 1 + D, -1);
						seg.update1(1, 1, 2 * D, -x + 1 + D, 100000 + D, 1);
					}
					break; 
				default : 
					assert(0);	
			}
		//	for (int i = -5; i <= 5; ++i) {
		//		printf("%d%c", seg.query(1, 1, 2 * D, i + D), " \n"[i == 5]);
		//	}
		}
		for (int i = 1; i <= n; ++i) {
			printf("%d%c", a[i] * seg.query(1, 1, 2 * D, a[i] + D), " \n"[i == n]);
		}
	}
	return 0;
}
