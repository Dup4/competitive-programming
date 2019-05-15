#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 500010
#define pii pair <int, int>
#define fi first
#define se second
const ll p = 1e9 + 7;
int n, a[N];
pii b[N];

struct SEG {
	struct node {
		ll sum, lazy, cnt;
		node () {
			sum = lazy = cnt = 0;
		}
		void add(ll x) {
			(sum += 1ll * x * cnt % p) %= p;
			(lazy += x) %= p;
		}
		node operator + (const node &other) const {
			node res = node();
			res.sum = sum + other.sum;
			res.cnt = cnt + other.cnt;
			return res;
		}
	}t[N << 2];
	void build(int id, int l, int r) {
		t[id] = node();
		t[id].cnt = r - l + 1;
		if (l == r) {
			return;
		}
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
	}
	void pushdown(int id) {
		ll &x = t[id].lazy;
		if (x == 0) {
			return;
		}
		t[id << 1].add(x);
		t[id << 1 | 1].add(x);
		x = 0;
	}
	void update(int id, int l, int r, int ql, int qr, ll x) {
		if (l >= ql && r <= qr) {
			t[id].add(x);
			return;
		}
		int mid = (l + r) >> 1;
		pushdown(id);
		if (ql <= mid) update(id << 1, l, mid, ql, qr, x);
		if (qr > mid) update(id << 1 | 1, mid + 1, r, ql, qr, x);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	ll query(int id, int l, int r, int ql, int qr) {
		if (l >= ql && r <= qr) {
			return t[id].sum;
		}
		int mid = (l + r) >> 1;
		pushdown(id);
		ll res = 0;
		if (ql <= mid) res = (res + query(id << 1, l, mid, ql, qr)) % p;
		if (qr > mid) res = (res + query(id << 1 | 1, mid + 1, r, ql, qr)) % p;
		return res;
	}
}seg[2];

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			b[i] = pii(a[i], i);
		}
		ll res = 0;
		sort(b + 1, b + 1 + n);
		for (int i = 0; i < 2; ++i) {
			seg[i].build(1, 1, n);
		}
		for (int i = 1; i <= n; ++i) {
			int pos = b[i].se;
			ll l = seg[0].query(1, 1, n, 1, pos);
			l = l * (n - pos + 1) % p;
			ll r = seg[1].query(1, 1, n, pos, n);
			res = (res + 1ll * l * r % p * b[i].fi % p) % p;
			seg[0].update(1, 1, n, 1, pos, 1);
			seg[1].update(1, 1, n, pos, n, 1);
		}
		printf("%lld\n", res);
	}
	return 0;
}
