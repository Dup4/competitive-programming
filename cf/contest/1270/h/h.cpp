#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10;
int n, q, a[N];

struct SEG {
	struct node {
		int cnt, Min;
		node() { cnt = 0; Min = 1e9; }
	}t[N << 2];
	void build(int id, int l, int r) {
		t[id] = node();
		if (l == r) return;
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
	}
	int query(int id, int l, int r, int v) { 
		if (l == r) return t[id].Min < v;
		int mid = (l + r) >> 1;
		if (t[id].Min >= v) return 0;
		if (t[id << 1].Min >= v) return query(id << 1 | 1, mid + 1, r, v); 
		else return t[id].cnt - t[id << 1].cnt + query(id << 1, l, mid, v);
	}
	void update(int id, int l, int r, int pos, int v) {
		if (l == r) {
			t[id].cnt = 1;
			t[id].Min = v;
			return;
		}
		int mid = (l + r) >> 1;
		if (pos <= mid) update(id << 1, l, mid, pos, v);
		else update(id << 1 | 1, mid + 1, r, pos, v);
		t[id].cnt = t[id << 1].cnt + query(id << 1 | 1, mid + 1, r, t[id << 1].Min);
		t[id].Min = min(t[id << 1].Min, t[id << 1 | 1].Min);
	}
}seg;

int main() {
	while (scanf("%d%d", &n, &q) != EOF) {
		seg.build(1, 1, n);
		for (int i = 1; i <= n; ++i) scanf("%d", a + i), seg.update(1, 1, n, i, a[i]);
		for (int i = 1, pos, x; i <= q; ++i) {
			scanf("%d%d", &pos, &x);
			seg.update(1, 1, n, pos, x);
			printf("%d\n", seg.t[1].cnt); 
		}
	}
	return 0;
}
