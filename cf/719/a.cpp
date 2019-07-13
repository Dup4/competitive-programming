#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
const ll p = 1e9 + 7;
int n, q, a[N];
void add(ll &x, ll y) {
	x += y;
	if (x >= p) x -= p;
}

struct SEG {
	struct Matrix {
		ll a[2][2];
		Matrix() {
			memset(a, 0, sizeof a);
		}
		bool isbase() {
			return (a[0][0] == 1 && a[1][1] == 1 && a[0][1] == 0 && a[1][0] == 0); 
		}
		void setbase() {
			memset(a, 0, sizeof a);
			a[0][0] = a[1][1] = 1;
		}
		Matrix operator * (const Matrix &other) const {
			Matrix res = Matrix();
			for (int i = 0; i < 2; ++i) {
				for (int j = 0; j < 2; ++j) {
					for (int k = 0; k < 2; ++k) {
						add(res.a[i][j], a[i][k] * other.a[k][j] % p);  
					}
				}
			}
			return res;
		}
		Matrix operator + (const Matrix &other) const {
			Matrix res = Matrix();
			for (int i = 0; i < 2; ++i) {
				for (int j = 0; j < 2; ++j) {
					add(res.a[i][j], (a[i][j] + other.a[i][j]) % p);
				}
			}
			return res;
		}
		Matrix operator ^ (ll n) const {
			Matrix res = Matrix();
			Matrix base = *this; 
			for (int i = 0; i < 2; ++i) {
				res.a[i][i] = 1;
			}
			while (n) {
				if (n & 1) {
					res = res * base;
				}
				base = base * base;
				n >>= 1;
			}
			return res;
		}
	}B, M, MX;
	struct node {
		Matrix a, lazy;
		node () {
			a = Matrix();
			lazy.setbase();
		}
		void add(Matrix M) {
			a = M * a;  
			lazy = lazy * M;
		}
		node operator + (const node &other) const {
			node res = node();
			res.lazy.setbase();
			res.a = a + other.a;
			return res;
		}
	}t[N << 2], res;
	void init() {
		B = Matrix();
		B.a[0][0] = 1;
		M = Matrix();
		M.a[0][0] = M.a[0][1] = M.a[1][0] = 1;
	}
	void build(int id, int l, int r) {
		if (l == r) {
			t[id].a = M ^ (a[l] - 1);
			return;
		}
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	void pushdown(int id) {
		Matrix &lazy = t[id].lazy;
		if (lazy.isbase()) return;
		t[id << 1].add(lazy);
		t[id << 1 | 1].add(lazy);
		lazy.setbase();
	}
	void update(int id, int l, int r, int ql, int qr, Matrix MX) {
		if (l >= ql && r <= qr) {
			t[id].add(MX);
			return;
		}
		int mid = (l + r) >> 1;
		pushdown(id);
		if (ql <= mid) update(id << 1, l, mid, ql, qr, MX);
		if (qr > mid) update(id << 1 | 1, mid + 1, r, ql, qr, MX);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	void query(int id, int l, int r, int ql, int qr) {
		if (l >= ql && r <= qr) {
			res = res + t[id];
			return;
		}
		int mid = (l + r) >> 1;
		pushdown(id);
		if (ql <= mid) query(id << 1, l, mid, ql, qr);
		if (qr > mid) query(id << 1 | 1, mid + 1, r, ql, qr);
	}
}seg;

int main() {
	while (scanf("%d%d", &n, &q) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		seg.init();
		seg.build(1, 1, n);
		int op, l, r, x;
		while (q--) {
			scanf("%d%d%d", &op, &l, &r);
			switch(op) {
				case 1 :
					scanf("%d", &x);
					seg.MX = seg.M ^ x;
					seg.update(1, 1, n, l, r, seg.MX);
					break;
				case 2 :
					seg.res = SEG::node();
					seg.query(1, 1, n, l, r);
					seg.res.a = seg.B * seg.res.a;
					printf("%lld\n", seg.res.a.a[0][0]);
					break;
			}
		}
			
	}
	return 0;
}
