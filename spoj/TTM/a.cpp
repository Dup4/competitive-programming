#include <bits/stdc++.h>
using namespace std; 
using ll = long long;
const int N = 1e5 + 10;
int n, q, a[N], rt[N]; 

struct SEG {
	struct node {
		int ls, rs;
		ll lazy, sum;
		node() { ls = rs = lazy = sum = 0; }
	}t[N * 40];
	int tot;
	int newnode() { ++tot; t[tot] = node();  return tot; }
	void init() { tot = 0; }
	void build(int &id, int l, int r) {
		if (!id) id = newnode();
		if (l == r) {
			t[id].sum = a[l];
			return;
		}
		int mid = (l + r) >> 1;
		build(t[id].ls, l, mid);
		build(t[id].rs, mid + 1, r);
		t[id].sum = t[t[id].ls].sum + t[t[id].rs].sum;
	}
	void update(int &now, int pre, int l, int r, int ql, int qr, ll v) {
		now = newnode();
		t[now] = t[pre];
		t[now].sum += v * (min(r, qr) - max(l, ql) + 1);
		if (l >= ql && r <= qr) {
			t[now].lazy += v;
			return;
		}
		int mid = (l + r) >> 1;
		if (ql <= mid) update(t[now].ls, t[pre].ls, l, mid, ql, qr, v);
		if (qr > mid) update(t[now].rs, t[pre].rs, mid + 1, r, ql, qr, v);
	}
	ll query(int id, int l, int r, int ql, int qr) {
		if (ql > qr) return 0;
		if (l >= ql && r <= qr) return t[id].sum;
		int mid = (l + r) >> 1;
		ll res = t[id].lazy * (min(r, qr) - max(l, ql) + 1);
		if (ql <= mid) res += query(t[id].ls, l, mid, ql, qr);
		if (qr > mid) res += query(t[id].rs, mid + 1, r, ql, qr);
		return res;
	}
}seg;

int main() {
	while (scanf("%d%d", &n, &q) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%d", a + i); 
		seg.init();
		seg.build(rt[0], 1, n);
		int cntrt = 0;
		char op; int l, r, t; ll d; 
		for (int i = 1; i <= q; ++i) {
			scanf(" %c", &op);
			if (op == 'C') {
				scanf("%d%d%lld", &l, &r, &d); 
				++cntrt;
				rt[cntrt] = rt[cntrt - 1];
				seg.update(rt[cntrt], rt[cntrt], 1, n, l, r, d);
			} else if (op == 'Q') {
				scanf("%d%d", &l, &r);
				printf("%lld\n", seg.query(rt[cntrt], 1, n, l, r));
			} else if (op == 'H') {
				scanf("%d%d%d", &l, &r, &t);
				printf("%lld\n", seg.query(rt[t], 1, n, l, r));
			} else {
				scanf("%d", &t);
				cntrt = t;
			}
		}
	}
	return 0;
}
