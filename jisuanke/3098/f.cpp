#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n, q, a[N];

struct SEG {
	int t[N << 2];
	void init() {
		memset(t, 0, sizeof t);
	}
	void update(int id, int l, int r, int pos, int x) {
		if (l == r) {
			t[id] = x;
			return;
		}
		int mid = (l + r) >> 1;
		if (pos <= mid) update(id << 1, l, mid, pos, x);
		else update(id << 1 | 1, mid + 1, r, pos, x);
		t[id] = t[id << 1] ^ t[id << 1 | 1];
	}
	int query(int id, int l, int r, int ql, int qr) {
		if (l >= ql && r <= qr) {
			return t[id];
		}
		int mid = (l + r) >> 1;
		int x = 0;
		if (ql <= mid) x ^= query(id << 1, l, mid, ql, qr);
		if (qr > mid) x ^= query(id << 1 | 1, mid + 1, r, ql, qr);
		return x;
	}
}seg[2];

int main() {
	int T; scanf("%d", &T);
	for (int kase = 1; kase <= T; ++kase) {
		printf("Case #%d:\n", kase);
		scanf("%d%d", &n, &q);
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		seg[0].init(); seg[1].init();
		for (int i = 1; i <= n; ++i) {
			seg[i % 2].update(1, 1, n, i, a[i]);
		}
		int op, x, y;
		while (q--) {
			scanf("%d%d%d", &op, &x, &y);
			switch(op) {
				case 0 :
					seg[x % 2].update(1, 1, n, x, y);
					break;
				case 1 :
					if ((y - x + 1) % 2 == 0) puts("0");
					else {
						printf("%d\n", seg[x % 2].query(1, 1, n, x, y));
					}
					break;
			}
		}
	}
	return 0;
}
