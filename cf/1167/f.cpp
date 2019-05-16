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
		ll sum, cnt;  
		node () {
			sum = 0;
		}
		void add(ll x) {
			sum = (sum + x * cnt % p) % p; 
		}
		node operator + (const node &other) const {
			node res = node();
			res.sum = sum + other.sum;
			return res;
		}
	}t[N << 2];
	void build(int id, int l, int r) {
		t[id] = node();
		if (l == r) {
			t[id].cnt = l;
			return;
		}
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
	}
	void update(int id, int l, int r, int pos, ll x) {
		if (l == r) {
			t[id].add(x);
			return;
		}
		int mid = (l + r) >> 1;
		if (pos <= mid) update(id << 1, l, mid, pos, x);
		else update(id << 1 | 1, mid + 1, r, pos, x);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	ll query(int id, int l, int r, int ql, int qr) {
		if (l >= ql && r <= qr) {
			return t[id].sum;
		}
		int mid = (l + r) >> 1;
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
			ll l = (seg[0].query(1, 1, n, 1, pos) + pos) % p;
			ll r = seg[1].query(1, 1, n, 1, n - pos + 1);   
			l = l * (n - pos + 1) % p;
			r = r * pos % p;
			res = (res + (l + r) % p * b[i].fi % p) % p;   
			seg[0].update(1, 1, n, pos, 1);
			seg[1].update(1, 1, n, n - pos + 1, 1);  
		}
		printf("%lld\n", res);
	}
	return 0;
}
