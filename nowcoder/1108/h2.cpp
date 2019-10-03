#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int N = 2e5 + 10;
int n, q; ll f[N];
struct node {
	int x, y, id; 
	bool isleft;
	node() {}
	node(int x, int y, int id) : x(x), y(y), id(id) { isleft = false; } 
	bool operator < (const node &other) const {
		if (x == other.x) return y > other.y;
		return x < other.x;
	}
}a[N], ta[N];

struct BIT {
	ll a[N];
	void init() { memset(a, 0, sizeof a); }
	void update(int x, int v) {
		for (; x < N; x += x & -x)
			a[x] += v;
	}
	ll query(int x) {
		ll res = 0;
		for (; x > 0; x -= x & -x)
			res += a[x];
		return res;
	}
	ll query(int l, int r) {
		if (l > r) return 0;
		return query(r) - query(l - 1);
	}
}bit; 

void gao(int l, int r) {
	if (l == r) return;
	int mid = (l + r) >> 1;
	gao(l, mid); gao(mid + 1, r); 
	for (int i = l; i <= r; ++i) {
		ta[i] = a[i];
		if (i <= mid) ta[i].isleft = true;
		else ta[i].isleft = false;
	}	
	sort(ta + l, ta + r + 1);
	for (int i = l; i <= r; ++i) {
		if (ta[i].isleft) {
			if (ta[i].id == 0)
				bit.update(ta[i].y, 1);
		}
		else {
			if (ta[i].id) {
				f[ta[i].id] += bit.query(ta[i].y, n);
			}
		}
	}
	for (int i = l; i <= r; ++i)
		if (ta[i].isleft && ta[i].id == 0)
			bit.update(ta[i].y, -1);
}

int main() {
	bit.init();
	while (scanf("%d%d", &n, &q) != EOF) {
		for (int i = 1, op, l, r; i <= q; ++i) {
			scanf("%d%d%d", &op, &l, &r);
			a[i] = node(l, r, op == 1 ? 0 : i);
			if (op == 1) f[i] = -1;
			else f[i] = 0;
		}
		gao(1, q);
		for (int i = 1; i <= q; ++i) if (f[i] != -1)
			printf("%lld\n", f[i]);
	}
	return 0;
}

