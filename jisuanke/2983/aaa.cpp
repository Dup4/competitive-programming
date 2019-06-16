#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 500010
const ll p = 998244353;
int n, a[N], b[N], f[N], g[N];
ll s[N], y[N]; 
ll qmod(ll base, ll n) {
	ll res = 1;
	while (n) {
		if (n & 1) {
			res = res * base % p;
		}
		base = base * base % p;
		n >>= 1;
	}
	return res;
}
void Hash() {
	b[0] = 0;
	for (int i = 1; i <= n; ++i) {
		b[++b[0]] = a[i];
	}
	sort(b + 1, b + 1 + b[0]);
	b[0] = unique(b + 1, b + 1 + b[0]) - b - 1;
	for (int i = 1; i <= n; ++i) {
		a[i] = lower_bound(b + 1, b + 1 + b[0], a[i]) - b;
	}
}

struct BIT {
	int a[N];
	void init() {
		memset(a, 0, sizeof a); 
	}
	void update(int x, int v) {
		for (; x < N; x += x & -x) {
			a[x] = max(a[x], v); 
		}
	}
	int query(int x) {
		int res = 0;
		for (; x > 0; x -= x & -x) {
			res = max(res, a[x]); 
		}
		return res;
	}
}bit;

struct SEG {
	struct node {
		int ls, rs;
		ll tot;
		node() {
			ls = rs = 0;
			tot = 0;
		}
		node(int ls, int rs, ll tot) : ls(ls), rs(rs), tot(tot) {}
	}t[N * 60];
	int rt[N];
	int cnt;
	void init() {
		memset(rt, 0, sizeof rt);
		cnt = 0;
		t[0] = node();
	}
	void update(int &id, int l, int r, int x, ll v) {
		if (!id) {
			id = ++cnt;
			t[id] = node();
		}
		if (l == r) {
			(t[id].tot += v) %= p;
			return;
		}
		int mid = (l + r) >> 1;
		if (x <= mid) update(t[id].ls, l, mid, x, v);
		else update(t[id].rs, mid + 1, r, x, v);
		t[id].tot = (t[t[id].ls].tot + t[t[id].rs].tot) % p;
	}  
	ll query(int id, int l, int r, int ql, int qr) {
		if (ql > qr) return 0;
		if (!id) return 0;
		if (l >= ql && r <= qr) {
			return t[id].tot;
		}
		int mid = (l + r) >> 1;
		ll res = 0;
		if (ql <= mid) res = (res + query(t[id].ls, l, mid, ql, qr)) % p;
		if (qr > mid)  res = (res + query(t[id].rs, mid + 1, r, ql, qr)) % p;
		return res;
	}
}seg;


int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
	}
	Hash();
	bit.init();
	int Max = 0; 
	for (int i = 1; i <= n; ++i) {
		f[i] = bit.query(a[i] - 1) + 1;
		bit.update(a[i], f[i]);
		Max = max(Max, f[i]);
	}
	seg.init();
	for (int i = 1; i <= n; ++i) {
		if (f[i] == 1) {  
			s[i] = 1;
		} else {
			s[i] = seg.query(seg.rt[f[i] - 1], 1, b[0], 1, a[i] - 1);
		}
		seg.update(seg.rt[f[i]], 1, b[0], a[i], s[i]);
	}
	bit.init();
	b[0] += 2;
	for (int i = n; i >= 1; --i) {
		g[i] = bit.query(b[0] - (a[i] + 1)) + 1;
		bit.update(b[0] - a[i], g[i]);	
	}
	seg.init();
	for (int i = n; i >= 1; --i) {
		if (f[i] == Max) {
			y[i] = 1;	
		} else {
			y[i] = seg.query(seg.rt[f[i] + 1], 1, b[0], a[i] + 1, b[0]);
		}
		seg.update(seg.rt[f[i]], 1, b[0], a[i], y[i]);
	}
	ll tot = 0;
	for (int i = 1; i <= n; ++i) {
		s[i] = s[i] * y[i] % p;
		if (f[i] == Max) {
			tot = (tot + s[i]) % p;
		}
	}
	ll inv = qmod(tot, p - 2); 
	for (int i = 1; i <= n; ++i) {
		printf("%lld%c", s[i] * inv % p, " \n"[i == n]);
	}
	return 0;
}
