#include <bits/stdc++.h>
using namespace std;

typedef long long ll; 
const int N = 1e5 + 10;
const int m = 1e5;
int n, a[N], b[N], c[N], Ta[N], Tb[N], Tc[N], sum[N], A[N];
ll res;

struct SEG {
	struct node {
		ll base, sum, lazy;
		node() { base = sum = lazy = 0; }
		void up(ll x) {
			sum += base * x;
			lazy += x;
		}
		node operator + (const node &other) const {
			node res = node();
			res.sum = sum + other.sum;
			res.base = base + other.base;
			return res;
		}
	}t[N << 2];
	void down(int id) {
		ll &lazy = t[id].lazy;
		if (!lazy) return;
		t[id << 1].up(lazy);
		t[id << 1 | 1].up(lazy);
		lazy = 0;
	}
	void build(int id, int l, int r) {
		t[id] = node();
		if (l == r) {
			t[id].base = A[l];
			return;
		}
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	void update(int id, int l, int r, int ql, int qr, ll v) {
		if (l >= ql && r <= qr) {
			t[id].up(v);
			return;
		}
		int mid = (l + r) >> 1;
		down(id);
		if (ql <= mid) update(id << 1, l, mid, ql, qr, v);
		if (qr > mid) update(id << 1 | 1, mid + 1, r, ql, qr, v);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	ll query(int id, int l, int r, int ql, int qr) {
		if (l >= ql && r <= qr) return t[id].sum;
		int mid = (l + r) >> 1;
		down(id);
		ll res = 0;
		if (ql <= mid) res += query(id << 1, l, mid, ql, qr);
		if (qr > mid) res += query(id << 1 | 1, mid + 1, r, ql, qr);
		return res;
	}
}seg;
inline int get(int l, int r) {
	r = min(r, m);
	if (l > r) return 0;
	return sum[r] - sum[l - 1];
}
ll gao(int *a, int *b, int *c) {
	sum[0] = 0;
	for (int i = 1; i <= m; ++i) sum[i] = sum[i - 1] + c[i], A[i] = a[i]; 
	seg.build(1, 1, m);
	ll res = 0;
	seg.update(1, 1, m, 1, 1, c[1]); 
	for (int i = 1; i <= m; ++i) {
		seg.update(1, 1, m, i, i, get(i, i + i)); 
		if (i + i - 1 <= m && i > 1) {
			seg.update(1, 1, m, 1, i - 1, c[i + i - 1]);  
		}
		res += 1ll * b[i] * seg.query(1, 1, m, 1, i);
		seg.update(1, 1, m, 1, i, -c[i]);
	}
	return res;
}

int main() {
	int T; scanf("%d", &T);
	for (int kase = 1; kase <= T; ++kase) {
		printf("Case #%d: ", kase);
		scanf("%d", &n);
		memset(Ta, 0, sizeof Ta);
		memset(Tb, 0, sizeof Tb);
		memset(Tc, 0, sizeof Tc);
		for (int i = 1; i <= n; ++i) scanf("%d", a + i), ++Ta[a[i]];
		for (int i = 1; i <= n; ++i) scanf("%d", b + i), ++Tb[b[i]];
		for (int i = 1; i <= n; ++i) scanf("%d", c + i), ++Tc[c[i]];
		res = 0;
		res += gao(Ta, Tb, Tc);
		res += gao(Tc, Tb, Ta);
		res += gao(Tb, Ta, Tc);
		res += gao(Tc, Ta, Tb);
		res += gao(Ta, Tc, Tb);
		res += gao(Tb, Tc, Ta);
		printf("%lld\n", res);
	}
	return 0;
}
