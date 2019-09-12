#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e5 + 10;
int n, q; ll a[N];
struct SEG {
	struct node {
		int cnt;
		ll sum, lazy;
		node() { sum = lazy = 0; }
		void up(ll x) {
			sum += x * cnt;
			lazy += x;	
		}
		node operator + (const node &other) const {
			node res = node();
			res.cnt = cnt + other.cnt;
			res.sum = sum + other.sum;
			return res;
		}
	}t[N << 2], res;
	void down(int id) {
		ll &lazy = t[id].lazy;
		t[id << 1].up(lazy);
		t[id << 1 | 1].up(lazy);
		lazy = 0;
	}
	void build(int id, int l, int r) {
		t[id] = node();
		if (l == r) {
			t[id].cnt = 1;
			t[id].sum = a[l];
			return;
		}
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	void update(int id, int l, int r, int ql, int qr, ll v) {
		if (l >= ql && r <= qr) {
			t[id].up(v);
			return;
		}
		int mid = (l + r) >> 1;
		down(id);
		if (ql <= mid) update(id << 1, l, mid, ql, qr, v);
		if (qr > mid) update(id << 1 | 1, mid + 1, r, ql, qr, v);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	void query(int id, int l, int r, int ql, int qr) {
		if (l >= ql && r <= qr) {
			res = res + t[id];	
			return;
		}
		int mid = (l + r) >> 1;
		down(id);
		if (ql <= mid) query(id << 1, l, mid, ql, qr);
		if (qr > mid) query(id << 1 | 1, mid + 1, r, ql, qr);
	}
}seg;

int main() {
	while (scanf("%d%d", &n, &q) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%lld", a + i);
		seg.build(1, 1, n);	
		int op, l, r; ll v;
		for (int i = 1; i <= q; ++i) {
			scanf("%d%d%d", &op, &l, &r);
			if (op == 1) {
				scanf("%lld", &v);
				seg.update(1, 1, n, l, r, v);
			} else {
				seg.res = SEG::node();
				seg.query(1, 1, n, l, r);
				printf("%lld\n", seg.res.sum);
			}
		}		
	}
	return 0;
}
