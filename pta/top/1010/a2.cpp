#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int n, a[N], b[N];

struct SEG {
	int t[N << 2];
	void init() { memset(t, 0, sizeof t); }
	void update(int id, int l, int r, int pos, int v) {
		if (l <= pos && r >= pos) t[id] += v;
		if (l == r) return;
		int mid = (l + r) >> 1;
		if (pos <= mid) update(id << 1, l, mid, pos, v);
		else update(id << 1 | 1, mid + 1, r, pos, v);
	}
	int query(int id, int l, int r, int ql, int qr) {
		if (ql > qr) return 0;
		if (l >= ql && r <= qr) return t[id];
		int mid = (l + r) >> 1;
		int res = 0;
		if (ql <= mid) res += query(id << 1, l, mid, ql, qr);
		if (qr > mid) res += query(id << 1 | 1, mid + 1, r, ql, qr);
		return res;
	}
}seg;

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			b[i] = a[i];
		}
		seg.init();
		sort(b + 1, b + 1 + n);
		for (int i = 1; i <= n; ++i) {
			a[i] = lower_bound(b + 1, b + 1 + n, a[i]) - b;
			seg.update(1, 1, 100000, a[i], 1);
		}
		for (int i = 1; i <= n; ++i) {
			seg.update(1, 1, 100000, a[i], -1);
			printf("%d%c", seg.query(1, 1, 100000, 1, a[i] - 1), " \n"[i == n]);
		}
	}
	return 0;
}
