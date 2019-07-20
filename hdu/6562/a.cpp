#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
const ll p = 1e9 + 7;
int n, q;

void add(ll &x, ll y) {
	x += y;
	if (x >= p) x -= p;
}
struct SEG {
	struct node {
		ll sum, len, cnt;
		ll A, B, lenAB; 
		node(ll _cnt = 0) {
			cnt = _cnt;
			sum = 0;
			A = B = 0;
			len = lenAB = 1;
		}
		void add(ll _A, ll _B, ll _lenAB) {
			len = len * _lenAB % p;
			sum = (_A * len % p + sum * _lenAB % p + cnt * _B % p) % p;
			len = len * _lenAB % p;
			A = (_A * lenAB % p + A) % p;	
			B = (B * _lenAB % p + _B) % p;
			lenAB = lenAB * _lenAB % p;
		}
		node operator + (const node &other) const {
			node res = node();
			res.sum = (sum + other.sum) % p;
			res.len = (len + other.len) % p;
			res.cnt = cnt + other.cnt;
			return res;
		}
	}t[N << 2];
	void build(int id, int l, int r) {
		t[id] = node(r - l + 1);
		if (l == r) {
			return;
		}
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	void pushdown(int id) {
		ll &A = t[id].A;
		ll &B = t[id].B;
		ll &lenAB = t[id].lenAB;
		if (lenAB == 1) return;
		t[id << 1].add(A, B, lenAB);
		t[id << 1 | 1].add(A, B, lenAB);
		A = B = 0;
		lenAB = 1;
	}
	void update(int id, int l, int r, int ql, int qr, ll _A, ll _B, ll _lenAB) {
		if (l >= ql && r <= qr) {
			t[id].add(_A, _B, _lenAB);
			return;
		}
		int mid = (l + r) >> 1;
		pushdown(id);
		if (ql <= mid) update(id << 1, l, mid, ql, qr, _A, _B, _lenAB);
		if (qr > mid) update(id << 1 | 1, mid + 1, r, ql, qr, _A, _B, _lenAB);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	ll query(int id, int l, int r, int ql, int qr) {
		if (l >= ql && r <= qr) return t[id].sum;
		int mid = (l + r) >> 1;
		pushdown(id);
		ll res = 0;
		if (ql <= mid) add(res, query(id << 1, l, mid, ql, qr));
		if (qr > mid) add(res, query(id << 1 | 1, mid + 1, r, ql, qr));
		return res;
	}
}seg;

int main() {
	int T; scanf("%d", &T);
	for (int kase = 1; kase <= T; ++kase) {
		printf("Case %d:\n", kase);
		scanf("%d%d", &n, &q);
		seg.build(1, 1, n);
		char op[10]; int l, r, d;
		while (q--) {
			scanf("%s%d%d", op, &l, &r);
			switch(op[0]) {
				case 'w' :
					scanf("%d", &d);
					seg.update(1, 1, n, l, r, d, d, 10);
					break;
				case 'q' :
					printf("%lld\n", seg.query(1, 1, n, l, r));
					break;
			}		
		}
	}
	return 0;
}
