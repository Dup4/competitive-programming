#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
int n, q, arr[N];
struct SEG {
	struct node {
		int sze;
		ll sum, cnt;
		ll a, b;
		node () {
			sze = 0;
			sum = cnt = a = b = 0;
		}
		void add(ll _a, ll _b) {
			sum += _a * sze + _b * cnt;
			a += _a; b += _b;
		}
		node operator + (const node &other) const {
			node res = node();
			res.sze = sze + other.sze;
			res.cnt = cnt + other.cnt + sze * other.sze; 
			res.sum = sum + other.sum;
			return res;  
		}
	}t[N << 2];
	void build(int id, int l, int r) {
		if (l == r) {
			t[id] = node();
			t[id].sum = arr[l];
			t[id].sze = 1;
			return;
		}
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}	
	void pushdown(int id) {
		ll &a = t[id].a, &b = t[id].b;
		if (a == 0 && b == 0) {
			return;
		}
		t[id << 1].add(a, b);
		a += b * (t[id << 1].sze); 
		t[id << 1 | 1].add(a, b);
		a = 0, b = 0;
	}
	void update(int id, int l, int r, int ql, int qr, ll a, ll b) {
		if (l >= ql && r <= qr) {
			t[id].add(a + b * (l - ql), b);
			return;
		}
		int mid = (l + r) >> 1;
		pushdown(id);
		if (ql <= mid) {
			update(id << 1, l, mid, ql, qr, a, b); 
		} 
		if (qr > mid) {
			update(id << 1 | 1, mid + 1, r, ql, qr, a, b);
		}
		t[id] = t[id << 1] + t[id << 1 | 1]; 
	}
	ll query(int id, int l, int r, int pos) {
		if (l == r) {
			return t[id].sum;
		}
		int mid = (l + r) >> 1;
		pushdown(id);
		if (pos <= mid) {
			return query(id << 1, l, mid, pos);
		} else {
			return query(id << 1 | 1, mid + 1, r, pos);
		}
	}
}seg;

int main() {
	while (scanf("%d%d", &n, &q) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", arr + i);
		}
		seg.build(1, 1, n);
		int op, l, r, k, d, p;
		while (q--) {
			scanf("%d", &op);
			switch(op) {
				case 1 : 
					scanf("%d%d%d%d", &l, &r, &k, &d);
					seg.update(1, 1, n, l, r, k, d);
					break;
				case 2 :
					scanf("%d", &p);
					printf("%lld\n", seg.query(1, 1, n, p));
					break;
				default :
					assert(0);
			}
		}
	}
	return 0;
}
