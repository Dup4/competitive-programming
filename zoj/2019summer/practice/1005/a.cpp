#include <bits/stdc++.h>
using namespace std;

#define N 1000010
int n, m, q, a[N], b[N], tot; 
int res[N]; 
struct qnode {
	//-1删除 0 询问 1添加
	int tp, id, l, r, k, x;
	qnode() {}
	qnode(int tp, int id, int l, int r, int k, int x) : tp(tp), id(id), l(l), r(r), k(k), x(x) {}
}qrr[N], qleft[N], qright[N];

struct BIT {
	int a[N];
	void init() {
		memset(a, 0, sizeof a);
	}
	void update(int x, int v) {
		for (; x < N; x += x & -x) {
			a[x] += v;
		}
	}
	int query(int x) {
		int res = 0;
		for (; x > 0; x -= x & -x) {
			res += a[x];
		}
		return res;
	}
	int query(int l, int r) {
		if (l > r) return 0;
		return query(r) - query(l - 1);
	}
}bit;

void solve(int l, int r, int L, int R) {
	if (l > r) return;
	if (L == R) {
		for (int i = l; i <= r; ++i) {
			if (qrr[i].tp == 0) {
				res[qrr[i].id] = min(b[qrr[i].x], b[L]);
			}
		}
		return;
	}
	int MID = (L + R) >> 1;
	int cntl = 0, cntr = 0, cnt = l - 1;
	for (int i = l; i <= r; ++i) {
		if (qrr[i].tp) { //修改操作
			if (qrr[i].x <= MID) {
				qleft[++cntl] = qrr[i];
				bit.update(qrr[i].k, qrr[i].tp);
			} else {
				qright[++cntr] = qrr[i];
			}
		} else { //查询操作
			int tot = bit.query(qrr[i].l, qrr[i].r);
			if (tot >= qrr[i].k) {
				qleft[++cntl] = qrr[i];
			} else {
				qright[++cntr] = qrr[i];
				qright[cntr].k -= tot;
			}
		}
	}
	for (int i = l; i <= r; ++i) {
		if (qrr[i].tp && qrr[i].x <= MID) {
			bit.update(qrr[i].k, -qrr[i].tp); 
		}
	}
	for (int i = 1; i <= cntl; ++i) {
		qrr[++cnt] = qleft[i];
	}
	for (int i = 1; i <= cntr; ++i) {
		qrr[++cnt] = qright[i];
	} 
	solve(l, l + cntl - 1, L, MID);
	solve(l + cntl, r, MID + 1, R);
}

int main() {
	while (scanf("%d%d", &n, &q) != EOF) {
		bit.init();
		memset(res, -1, sizeof res);
		m = 0; tot = 0;
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			qrr[++m] = qnode(1, 0, 0, 0, i, a[i]);
			b[++tot] = a[i]; 
		}
		char op[10]; int x, y;
		for (int i = 1; i <= q; ++i) {
			scanf("%s%d%d", op + 1, &x, &y);
			switch(op[1]) {
				case 'C' :
					qrr[++m] = qnode(-1, 0, 0, 0, x, a[x]);
					qrr[++m] = qnode(1, 0, 0, 0, x, a[x] = y);
					b[++tot] = a[x]; 
					break;
				case 'Q' :
					if (x > y) {
						res[i] = 0;	
					} else {
						//CDQ要求的是第k小，y - x + 1从第k大转化成第k小
						qrr[++m] = qnode(0, i, 1, y, y - x + 1, a[y]); 
					}
					break;
			}
		}
		sort(b + 1, b + 1 + tot);
		tot = unique(b + 1, b + 1 + tot) - b - 1;
		for (int i = 1; i <= m; ++i) {
			qrr[i].x = lower_bound(b + 1, b + 1 + tot, qrr[i].x) - b;
		}
		solve(1, m, 1, tot);
		for (int i = 1; i <= q; ++i) {
			if (res[i] != -1) {
				printf("%d\n", res[i]);
			}
		}
	}
	return 0;
}
