#include <bits/stdc++.h>
using namespace std;

#define N 300010
int n, a[N], b[N];
int cnt[N], nx[N], f[N];

struct SEG {
	int a[N << 2];
	void build(int id, int l, int r) {
		a[id] = 1e9;
		if (l == r) return;
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
	}
	void update(int id, int l, int r, int pos, int x) {
		if (l == r) {
			a[id] = x;
			return;
		}
		int mid = (l + r) >> 1;
		if (pos <= mid) update(id << 1, l, mid, pos, x);
		else update(id << 1 | 1, mid + 1, r, pos, x);
		a[id] = min(a[id << 1], a[id << 1 | 1]);
	}
	int query(int id, int l, int r, int ql, int qr) {
		if (ql > qr) return 1e9;
		if (l >= ql && r <= qr) {
			return a[id];
		}
		int mid = (l + r) >> 1;
		int res = 1e9;
		if (ql <= mid) res = min(res, query(id << 1, l, mid, ql, qr));
		if (qr > mid) res = min(res, query(id << 1 | 1, mid + 1, r, ql, qr));
		return res;
	}
}seg;

bool work() {
	for (int i = 1; i <= n; ++i) {
		cnt[i] = 0;
	}
	for (int i = 1; i <= n; ++i) {
		++cnt[a[i]];
		--cnt[b[i]];
	}
	for (int i = 1; i <= n; ++i) {
		if (cnt[i] != 0) {
			return 0;
		}
	}
	seg.build(1, 1, n);
	for (int i = n; i >= 1; --i) {
		nx[i] = n + 1;
	}
	for (int i = n; i >= 1; --i) {
		f[i] = nx[a[i]];
		nx[a[i]] = i;
	}
//	for (int i = 1; i <= n; ++i) {
//		printf("%d %d\n", i, nx[i]);
//	}
	for (int i = 1; i <= n; ++i) {
		seg.update(1, 1, n, i, nx[i]);
	}
	for (int i = 1; i <= n; ++i) {
		if (seg.query(1, 1, n, 1, b[i] - 1) < nx[b[i]]) return 0;
		nx[b[i]] = f[nx[b[i]]];
		seg.update(1, 1, n, b[i], nx[b[i]]);
	}
	return 1;
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
		}
		for (int i = 1; i <= n; ++i) {
			scanf("%d", b + i);
		}
		puts(work() ? "YES" : "NO");
	}
	return 0;
}
