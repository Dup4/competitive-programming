#include <bits/stdc++.h>
using namespace std;

#define N 50010
int n, q, a[N];

struct SEG {
	struct node {
		int d[32];
		node() {
			memset(d, 0, sizeof d);
		}
		void insert(int x) {
			for (int i = 30; i >= 0; --i) {
				if ((x >> i) & 1) {
					if (!d[i]) {
						d[i] = x;
						break;
					} else {
						x ^= d[i];
					}
				}
			} 
		}
		node operator + (const node &other) const {
			node res = *this;
			for (int i = 30; i >= 0; --i) {
				if (other.d[i]) {
					res.insert(other.d[i]);
				}
			}
			return res;
		}
		int Max() {
			int res = 0;
			for (int i = 30; i >= 0; --i) {
				if ((res ^ d[i]) > res) {
					res = res ^ d[i];
				}
			}
			return res;
		}
	}t[N << 2], res;
	void build(int id, int l, int r) {
		if (l == r) {
			t[id] = node();
			t[id].insert(a[l]);
			return;
		}
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	void update(int id, int l, int r, int pos) {
		if (l == r) {
			t[id] = node();
			t[id].insert(a[l]);
			return;
		}
		int mid = (l + r) >> 1;
		if (pos <= mid) update(id << 1, l, mid, pos);
		else update(id << 1 | 1, mid + 1, r, pos);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	void query(int id, int l, int r, int ql, int qr) {
		if (l >= ql && r <= qr) {
			res = res + t[id];
			return;
		}
		int mid = (l + r) >> 1;
		if (ql <= mid) query(id << 1, l, mid, ql, qr);
		if (qr > mid) query(id << 1 | 1, mid + 1, r, ql, qr);
	}
}seg;

int main() {
	while (scanf("%d%d", &n, &q) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		for (int i = n; i >= 1; --i) a[i] ^= a[i - 1]; 
		seg.build(1, 1, n);
		int op, l, r, v;
		while (q--) {
			scanf("%d%d%d", &op, &l, &r);
			if (op == 1) {
				scanf("%d", &v);
				a[l] ^= v;
				a[r + 1] ^= v;
				seg.update(1, 1, n, l);
				if (r < n) seg.update(1, 1, n, r + 1);
			} else {
				seg.res = SEG::node();
				seg.query(1, 1, n, l, r);
				printf("%d\n", seg.res.Max());
			}
		}
	}
	return 0;
}
