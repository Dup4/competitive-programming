#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
int n, q, arr[N];

struct SEG {
	struct node {
		int cnt;
		ll sum1, sum2;
		node () {
			cnt = sum1 = sum2 = 0;
		}
		node (int cnt, ll sum1, ll sum2) : cnt(cnt), sum1(sum1), sum2(sum2) {}
		node operator + (const node &other) const {
			node res = node();
			res.cnt = cnt + other.cnt;
			res.sum1 = sum1 + other.sum1;
			res.sum2 = sum2 + other.sum2 + other.sum1 * cnt;
			return res;
		}
	}t[N << 2], res;
	void build(int id, int l, int r) {
		if (l == r) {
			t[id] = node(1, arr[l], arr[l]);
			return;
		}
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	void update(int id, int l, int r, int pos, int v) {
		if (l == r) {
			t[id] = node(1, v, v);
			return;
		}
		int mid = (l + r) >> 1;
		if (pos <= mid) update(id << 1, l, mid, pos, v);
		else update(id << 1 | 1, mid + 1, r, pos, v);
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
		for (int i = 1; i <= n; ++i) {
			scanf("%d", arr + i);
		}
		seg.build(1, 1, n);
		int op, x, y;
		while (q--) {
			scanf("%d%d%d", &op, &x, &y);
			switch(op) {
				case 1 :
					seg.update(1, 1, n, x, y);
					break;
				case 2 :
					seg.res = SEG::node(0, 0, 0);
					seg.query(1, 1, n, x, y);
					printf("%lld\n", seg.res.sum2); 	
					break;
				default :
					assert(0);
			}
		}
	}
	return 0;
}
