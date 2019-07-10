#include <bits/stdc++.h>
using namespace std;

#define db double
#define N 100010
const db eps = 1e-7;
int q, ans, tot;
db K[N], B[N];
struct SEG {
	struct node {
		bool F;
		int pos; 
		db k, b;
		node() {}
		void set(int pos, db k, db b) {
			this->pos = pos;
			this->k = k;
			this->b = b;
		}
	}t[N << 2];
	void init() {
		memset(t, 0, sizeof t);
	}
	void update(int id, int l, int r, int pos, db k, db b) {
		if (!t[id].F) {
			t[id].F = 1;
			t[id].set(pos, k, b);
			return;
		}
		int mid = (l + r) >> 1;
		db kk = t[id].k, bb = t[id].b;
		db l1 = l * kk + bb, r1 = r * kk + bb;
		db l2 = l * k + b, r2 = r * k + b;
		if (l1 >= l2 && r1 >= r2) return;
		if (l2 > l1 && r2 > r1) {
			t[id].set(pos, k, b);
			return;
		}
		db x = (bb - b) / (k - kk);
		//交点在左边
		if (x <= mid) {
			//原左端点高于新左端点, 那么原线的覆盖范围小，用新线覆盖当前区域，原线递归下去更新
			if (l1 > l2) {
				update(id << 1, l, mid, t[id].pos, t[id].k, t[id].b);
				t[id].set(pos, k, b);
			} else { //原线的覆盖范围大，直接用新线递归更新
				update(id << 1, l, mid, pos, k, b);
			}
		} else { //交点在右边
			if (l1 > l2) { //原线的覆盖范围大
				update(id << 1 | 1, mid + 1, r, pos, k, b);
			} else { //原线的覆盖范围小
				update(id << 1 | 1, mid + 1, r, t[id].pos, t[id].k, t[id].b);
				t[id].set(pos, k, b);
			}
		}
	}
	//找到线段所管辖的区域
	void update(int id, int l, int r, int ql, int qr, int pos, db k, db b) {
		if (l >= ql && r <= qr) {
			update(id, l, r, pos, k, b);
			return;
		}
		int mid = (l + r) >> 1;
		if (ql <= mid) update(id << 1, l, mid, ql, qr, pos, k, b);
		if (qr > mid) update(id << 1 | 1, mid + 1, r, ql, qr, pos, k, b);
	}
	void Cmax(int &a, int b, int x) {
		db ya = K[a] * x + B[a];
		db yb = K[b] * x + B[b];
		if (ya < yb || (fabs(ya - yb) < eps && a > b)) a = b;
	}
	int query(int id, int l, int r, int x) {
		if (l == r) return t[id].pos;
		int mid = (l + r) >> 1;
		int res = t[id].pos;
		if (x <= mid) Cmax(res, query(id << 1, l, mid, x), x);
		else Cmax(res, query(id << 1 | 1, mid + 1, r, x), x);
		return res;
	}
}seg;

int main() {
	while(scanf("%d", &q) != EOF) {
		int n = 100000;
		int op, x[2], y[2];
		int mod = 39989;
		ans = 0;
		for (int _q = 1; _q <= q; ++_q) {
			scanf("%d", &op);
			switch(op) {
				case 0 :
					scanf("%d", x);
					x[0] = (x[0] + ans - 1) % mod + 1;
					printf("%d\n", ans = seg.query(1, 1, n, x[0]));
					break;
				case 1 :
					for (int i = 0; i < 2; ++i) {
						scanf("%d%d", x + i, y + i);
						x[i] = (x[i] + ans - 1) % mod + 1;
						y[i] = (y[i] + ans - 1) % 1000000000 + 1;
					}
					if (x[0] > x[1]) {
						swap(x[0], x[1]);
						swap(y[0], y[1]);
					}
					++tot;
					K[tot] = 1.0 * (y[0] - y[1]) / (x[0] - x[1]);
					B[tot] = y[0] - K[tot] * x[0];
					seg.update(1, 1, n, x[0], x[1], tot, K[tot], B[tot]);
					break;
			}
		}
	} 
	return 0;
}
