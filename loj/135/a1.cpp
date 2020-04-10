#include <bits/stdc++.h>
using namespace std;
const int N = 2100;
struct SEG {
	#define son1(u) ((u << 2) - 2)
	#define son2(u) ((u << 2) - 1)
	#define son3(u) (u << 2)
	#define son4(u) ((u << 2) | 1)
	int calc(int x0, int y0, int x1, int y1) { return (y1 - y0 + 1) * (x1 - x0 + 1); }
	struct node {
		short x[2], y[2];
		int sum, lazy;
		node() {}
		node(short x0, short y0, short x1, short y1, int _sum, int _lazy) {
			x[0] = x0;
			y[0] = y0;
			x[1] = x1;
			y[1] = y1;
			sum = _sum;
			lazy = _lazy;
		}
		int calc() { return (int)(y[1] - y[0] + 1) * (int)(x[1] - x[0] + 1); }
		void add(int val) {
			lazy += val;
			sum += calc() * val;
		}
	}a[(int)(N * N * 1.9)];
	void pushup(int now) {
		a[now].sum = 0;
		for (int i = 0; i < 4; ++i)
			a[now].sum += a[4 * now - 2 + i].sum; 
	}
	void pushdown(int now) {
		if (!a[now].lazy) return;
		for (int i = 0; i < 4; ++i)
			a[4 * now - 2 + i].add(a[now].lazy);
		a[now].lazy = 0; 
	}
	void build(int now, short x0, short y0, short x1, short y1) {
		a[now] = node(x0, y0, x1, y1, 0, 0);
		if (x0 == x1 && y0 == y1) return;
		int midx = (x0 + x1) >> 1;
		int midy = (y0 + y1) >> 1;
		if (x0 == x1) {
			build(son1(now), x0, y0, midx, midy);
			build(son3(now), x0, midy + 1, midx, y1);
		} else if (y0 == y1) {
			build(son1(now), x0, y0, midx, midy);
			build(son2(now), midx + 1, y0, x1, midy); 
		} else {
			build(son1(now), x0, y0, midx, midy);
			build(son2(now), midx + 1, y0, x1, midy); 
			build(son3(now), x0, midy + 1, midx, y1); 
			build(son4(now), midx + 1, midy + 1, x1, y1); 
		}
	}
	void update(int now, short x0, short y0, short x1, short y1, int val) {
		if (x0 > a[now].x[1] || x1 < a[now].x[0]) return; 
		if (y0 > a[now].y[1] || y1 < a[now].y[0]) return;  
		if (a[now].x[0] >= x0 && a[now].x[1] <= x1 && a[now].y[0] >= y0 && a[now].y[1] <= y1) {
			a[now].add(val); 
			return;
		}
		pushdown(now);
		for (int i = 0; i < 4; ++i)
			update(4 * now - 2 + i, x0, y0, x1, y1, val);  
		pushup(now);
	}
	int query(int now, short x0, short y0, short x1, short y1) {
		if (x0 > a[now].x[1] || x1 < a[now].x[0]) return 0; 
		if (y0 > a[now].y[1] || y1 < a[now].y[0]) return 0;
		if (a[now].x[0] >= x0 && a[now].x[1] <= x1 && a[now].y[0] >= y0 && a[now].y[1] <= y1)
			return a[now].sum;
		pushdown(now);
		int res = 0;
		for (int i = 0; i < 4; ++i)
			res += query(4 * now - 2 + i, x0, y0, x1, y1);
		pushup(now);
		return res;
	}
}seg;

int main() {
	int n, m, op, v;
	short x[2], y[2];
	scanf("%d%d", &n, &m);
	seg.build(1, 1, 1, n, m);
	while (scanf("%d%hd%hd%hd%hd", &op, x, y, x + 1, y + 1) != EOF) {
		if (op == 1) {
			scanf("%d", &v);
			if (x[0] > x[1]) swap(x[0], x[1]);
			if (y[0] > y[1]) swap(y[0], y[1]);
			seg.update(1, x[0], y[0], x[1], y[1], v);
		} else {
			if (x[0] > x[1]) swap(x[0], x[1]);
			if (y[0] > y[1]) swap(y[0], y[1]);
			printf("%d\n", seg.query(1, x[0], y[0], x[1], y[1])); 
		}
	}
	return 0;
}
