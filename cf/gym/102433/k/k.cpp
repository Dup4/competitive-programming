#include <bits/stdc++.h>
#define SZ(x) (int(x.size()))
#define fi first
#define se second
using namespace std;
using ll = long long;
using pII = pair<int, int>;
const int N = 5e5 + 10;
int n, m, q, segRt[N], id[N];
vector <vector<int>> vec;

struct SEG {
	struct node {
		pII val, lazy; 	
		void init() { val = lazy = pII(0, 0); }
		void up(pII _lazy) {
			val = _lazy;
			lazy = _lazy;
		}
	}t[N << 2], res; 
	void down(int id) {
		pII &lazy = t[id].lazy;
		if (lazy.fi == 0) return;
		t[id << 1].up(lazy);
		t[id << 1 | 1].up(lazy);
		lazy = pII(0, 0);
	}
	void build(int id, int l, int r) {
		t[id].init();
		if (l == r) return;
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
	}
	void update(int id, int l, int r, int ql, int qr, pII v) {
		if (l >= ql && r <= qr) {
			t[id].up(v);
			return;
		}
		int mid = (l + r) >> 1;
		down(id);
		if (ql <= mid) update(id << 1, l, mid, ql, qr, v);
		if (qr > mid) update(id << 1 | 1, mid + 1, r, ql, qr, v);
	}
	pII query(int id, int l, int r, int pos) {
	   if (l == r) return t[id].val;	
		int mid = (l + r) >> 1;
		down(id);
		if (pos <= mid) return query(id << 1, l, mid, pos);
		else return query(id << 1 | 1, mid + 1, r, pos);
	}
}seg;

struct TSEG {
	struct node {
		int ls, rs;
		int lazy, sum; 
		node() { ls = rs = lazy = sum = 0; }
	}t[N * 50]; 
	int tot;
	int newnode() { ++tot; t[tot] = node();  return tot; } 
	void init() { tot = 0; }
	void build(int &id, int l, int r, vector <int> &a) {
		id = newnode();
		if (l == r) {
			t[id].sum = a[l];
			return;
		}
		int mid = (l + r) >> 1;
		build(t[id].ls, l, mid, a);
		build(t[id].rs,mid + 1, r, a); 
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
	ll query(int id, int l, int r, int pos) { 
		if (l == r) return t[id].sum;
		int mid = (l + r) >> 1;
		ll res = t[id].lazy;
		if (pos <= mid) res += query(t[id].ls, l, mid, pos);
		else res += query(t[id].rs, mid + 1, r, pos);
		return res;
	}	
}tseg;

int main() {
	scanf("%d%d%d", &n, &m, &q);
	vec.resize(m + 1);
	seg.build(1, 1, n);
	tseg.init();
	for (int i = 1, sz; i <= m; ++i) {
		segRt[i] = 0;
		scanf("%d", &sz);
		vector <int> tmp(sz + 1);
		for (int j = 1, x; j <= sz; ++j) {
			scanf("%d", &x);
			tmp[j] = x;
		}
		vec[i] = tmp;	
	}
	for (int _q = 1; _q <= q; ++_q) {
		int op, i, l, r, p;
		scanf("%d", &op);
		if (op == 1) {
			scanf("%d%d", &i, &p);
			if (segRt[i]) {
				id[segRt[i]] = i;
				seg.update(1, 1, n, p, p + SZ(vec[i]) - 1, pII(segRt[i], p));
			}
		} else if (op == 2) {
			scanf("%d", &p);
			pII tmp = seg.query(1, 1, n, p);
			int res = 0;
			if (tmp.fi) {
				int pos = p - tmp.se + 1;
				res += tseg.query(tmp.fi, 1, SZ(vec[id[tmp.fi]]), pos) + vec[id[tmp.fi]][pos]; 
			}
			res %= 256;
			printf("%d\n", res);
		} else {
			scanf("%d%d%d", &i, &l, &r);
			tseg.update(segRt[i], segRt[i], 1, SZ(vec[i]), l, r, 1);
		}
	}
	return 0;
}
