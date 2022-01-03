#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 300010
#define INFLL 0x3f3f3f3f3f3f3f3f
int n, x, a[N];
ll sum[N]; 
ll f[N], g[N];

struct SEG {
	ll Max[N << 2];
	void build(int id, int l, int r) {
		if (l == r) {
			Max[id] = sum[l] * x + g[l];
			return;
		}
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
		Max[id] = max(Max[id << 1], Max[id << 1 | 1]);
	}
	ll query(int id, int l, int r, int ql, int qr) {
		if (l >= ql && r <= qr) {
			return Max[id];
		}
		int mid = (l + r) >> 1;
		ll Max = -INFLL;
		if (ql <= mid) Max = max(Max, query(id << 1, l, mid, ql, qr));
		if (qr > mid) Max = max(Max, query(id << 1 | 1, mid + 1, r, ql, qr));
		return Max;
	}
}seg;

int main() {
	while (scanf("%d%d", &n, &x) != EOF) {
		sum[0] = 0;
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			sum[i] = sum[i - 1] + a[i];
		}
		
		ll t = 0;
		for (int i = 1; i <= n; ++i) {
			t = min(t, sum[i]);
			f[i] = sum[i] - t;
		}
		t = -INFLL;
		for (int i = n; i >= 1; --i) {
			t = max(t, sum[i]);
			g[i] = t - sum[i];
		}
		/*
		for (int i = 1; i <= n; ++i) {
			printf("%d %lld %lld\n", i, f[i], g[i]);
		}
		*/
		seg.build(1, 1, n);
		ll res = 0;
		for (int i = 0; i <= n; ++i) {
			res = max(res, f[i] + seg.query(1, 1, n, i, n) - sum[i] * x);
		}
		printf("%lld\n", res);
	}
	return 0;
}
