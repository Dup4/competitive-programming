#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
const ll p = 1e9 + 7;
int n, m, a[N];
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
		Matrix operator ^ (int n) const {
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
	}B, M;
	struct node {
		Matrix a;
		ll lazy;
		node () {
			a = Matrix();
			lazy = 0;
		}
		void add(ll x) {
			a = (M ^ x) * a;
			lazy += x;
		}
		node operator + (const node &other) const {
			node res = node();
			res.a = a + other.a;
			return res;
		}
	}t[N << 2], res;
	void build(int id, int l, int r) {
		if (l == r) {
			t[id] = M ^ (a[l] - 1);
			return;
		}
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	void pushdown(int id) {
		ll &lazy = t[id].lazy;
		if (!lazy) return;
		t[id << 1].add(lazy);
		t[id << 1 | 1].add(lazy);
		lazy = 0;
	}
	void update(int id, int l, int r, int ql, int qr, int x) {
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
	while (scanf("%d%d", &n, &m) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		
	}
	return 0;
}
