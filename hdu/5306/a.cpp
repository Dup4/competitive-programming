#include <bits/stdc++.h>
using namespace std;

#define INF 0x3f3f3f3f
#define ll long long
#define N 1000010
int n, q, a[N];

struct SEG {
	struct node {
		ll sum;
	   	int Max[2], num, cnt, lazy;
		node() {
			num = sum = cnt = lazy = 0;
			Max[0] = -INF;
			Max[1] = -INF;
			lazy = INF;   
		}
		void add(int x) { 
			if (x >= Max[0]) return; 
			sum -= 1ll * num * (Max[0] - x); 
			Max[0] = x;
			lazy = x;  
		}
		node operator + (const node &other) const {
			node res = node();
			res.sum = sum + other.sum;
			res.cnt = cnt + other.cnt;
			if (Max[0] == other.Max[0]) {
				res.Max[0] = Max[0];
				res.num = num + other.num;
				if (res.num != res.cnt) {
					res.Max[1] = max(Max[1], other.Max[1]);
				} else {
					res.Max[1] = -INF;
				}
			} else {
				if (Max[0] > other.Max[0]) {
					res.Max[0] = Max[0];
					res.Max[1] = max(Max[1], other.Max[0]);
					res.num = num;
				} else {
					res.Max[0] = other.Max[0];
					res.Max[1] = max(other.Max[1], Max[0]);
					res.num = other.num;
				}
			}
			return res;
		}
	}t[N << 2], res; 
	void build(int id, int l, int r) {
		t[id] = node();
		if (l == r) {
			t[id].cnt = t[id].num = 1;
			t[id].Max[0] = a[l];
			t[id].sum = a[l];
			return;
		}
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	void pushdown(int id) {
		int &lazy = t[id].lazy;
		if (lazy == INF) return;
		t[id << 1].add(lazy);
		t[id << 1 | 1].add(lazy);
		lazy = INF;
	}
	void update(int id, int l, int r, int ql, int qr, int x) {
		if (x >= t[id].Max[0]) {
			return;
		}
		if (l == r) {
			x = min(x, t[id].Max[0]);
			t[id].sum = x;
			t[id].Max[0] = x;
			t[id].Max[1] = -INF;
			return;
		} 
		if (l >= ql && r <= qr) {
			if (x < t[id].Max[0] && x > t[id].Max[1]) {
				t[id].add(x);
				return;
			} 
		}
		int mid = (l + r) >> 1;
		pushdown(id); 
		if (ql <= mid) update(id << 1, l, mid, ql, qr, x);
		if (qr > mid) update(id << 1 | 1, mid + 1, r, ql, qr, x);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	void query(int id, int l, int r, int ql, int qr) {
		if (l >= ql && r <= qr) {
			res = res + t[id];
			return;
		}
		int mid = (l + r) >> 1;
		pushdown(id);
		if (ql <= mid) query(id << 1, l, mid, ql, qr);
		if (qr > mid) query(id << 1 | 1, mid + 1, r, ql, qr);
	}
}seg;

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &q);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
		}
		seg.build(1, 1, n);
		int op, x, y, t;
		while (q--) {
			scanf("%d%d%d", &op, &x, &y);
			if (!op) {
				scanf("%d", &t);
				seg.update(1, 1, n, x, y, t);
			} else {
				seg.res = SEG::node();
				seg.query(1, 1, n, x, y);
				printf("%lld\n", (op == 1 ? seg.res.Max[0] : seg.res.sum));
			}
		}
	}
	return 0;
}
