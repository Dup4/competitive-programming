#include <bits/stdc++.h>
using namespace std;
const int N = 8e4 + 10;
int n, q, a[N]; 

struct VSEG {
	struct node {
		int sum, Max, ls, rs; 
		node() {}
		void init() {
			sum = Max = 0;
			ls = rs = 0;
		}
	}t[N * 400];
	int cnt = 0;
	void init() { cnt = 0; }
	int newnode() {
		++cnt;
		t[cnt].init();
		return cnt;
	}
	void up(int id) {
		int ls = t[id].ls, rs = t[id].rs;
		t[id].sum = t[ls].sum + t[rs].sum;
		t[id].Max = max(t[ls].Max, t[rs].Max);
	}
	void update(int id, int l, int r, int pos, int v) {
		if (l == r) {
			t[id].sum += v;
			if (t[id].sum) t[id].Max = pos;
			else t[id].Max = 0;
			return;
		}
		int mid = (l + r) >> 1;
		if (pos <= mid) {
			if (!t[id].ls) t[id].ls = newnode();
			update(t[id].ls, l, mid, pos, v);
		} else {
			if (!t[id].rs) t[id].rs = newnode();
			update(t[id].rs, mid + 1, r, pos, v);
		}
		up(id);
	}
	int query(int id, int l, int r, int pos) { 
		if (!id) return 0;
		if (l == r) return t[id].sum;
		int mid = (l + r) >> 1;
		if (pos <= mid) return query(t[id].ls, l, mid, pos);
		else return query(t[id].rs, mid + 1, r, pos);
	}
}vseg;

struct SEG {
	struct node {
		int id, lazy, l, r; 
		node() {}
		void init() {
			id = l = r = 0;
		}
	}t[N << 2];
	vector <int> vec;
	void build(int id, int l, int r) { 
		t[id].l = l; t[id].r = r;
		t[id].id = vseg.newnode();
		for (int i = l; i <= r; ++i) {
			vseg.update(t[id].id, 1, n, a[i], 1); 
		}
		t[id].lazy = n;
		if (l == r) {
			t[id].lazy = a[l]; 
			return;
		}
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
	}
	void down(int id) {
		int &lazy = t[id].lazy;
		t[id << 1].lazy = min(lazy, t[id << 1].lazy);
		t[id << 1 | 1].lazy = min(lazy, t[id << 1 | 1].lazy);
		for (auto &it : {t[id << 1].id, t[id << 1 | 1].id}) {
			while (vseg.t[it].Max > lazy) { 
				int pos = vseg.t[it].Max;
				int del = vseg.query(it, 1, n, pos);
				vseg.update(it, 1, n, pos, -del);
				vseg.update(it, 1, n, lazy, del);
			}
		}
	}
	void update(int id, int l, int r, int ql, int qr, int x) {
		if (l >= ql && r <= qr) {
			vector <int> vec;
			int it = id;
			while (it) {
				vec.push_back(t[it].id);
				it >>= 1;
			}
			while (vseg.t[t[id].id].Max > x) {
				int pos = vseg.t[t[id].id].Max;
				int del = vseg.query(t[id].id, 1, n, pos);
				for (auto &it : vec) {
					vseg.update(it, 1, n, pos, -del);
					vseg.update(it, 1, n, x, del);
				}
			}
			t[id].lazy = min(t[id].lazy, x);
			return;
		}
		int mid = (l + r) >> 1;
		down(id);
		if (ql <= mid) update(id << 1, l, mid, ql, qr, x);
		if (qr > mid) update(id << 1 | 1, mid + 1, r, ql, qr, x);
	}
	void add(int id, int l, int r, int ql, int qr) {
		if (l >= ql && r <= qr) {
			vec.push_back(t[id].id);
			return;
		}
		int mid = (l + r) >> 1;
		down(id);
		if (ql <= mid) add(id << 1, l, mid, ql, qr);
		if (qr > mid) add(id << 1 | 1, mid + 1, r, ql, qr);
	}
	int querygao(int l, int r, int k) {
		if (l == r) return l;
		int mid = (l + r) >> 1;
		int lsum = 0;
		for (auto &it : vec) lsum += vseg.t[vseg.t[it].ls].sum;
		if (lsum >= k) {
			for (auto &it : vec) it = vseg.t[it].ls;
			return querygao(l, mid, k);
		} else {
			for (auto &it : vec) it = vseg.t[it].rs; 
			return querygao(mid + 1, r, k - lsum);
		}
	}
	int query(int l, int r, int k) {
		vec.clear();	
		add(1, 1, n, l, r);
		return querygao(1, n, k);  
	}
}seg;

int main() {
	while (scanf("%d%d", &n, &q) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		vseg.init();
		seg.build(1, 1, n);
		for (int _q = 1, tp, l, r, x; _q <= q; ++_q) {
			scanf("%d%d%d%d", &tp, &l, &r, &x);
			if (tp == 1) {
				if (x >= n) continue;
				seg.update(1, 1, n, l, r, x);
			} else {
				printf("%d\n", seg.query(l, r, x));
			}
		}
	}
	return 0;
}
