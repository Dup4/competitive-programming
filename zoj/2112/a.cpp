#include <bits/stdc++.h>
using namespace std;
const int N = 5e4 + 10;
int n, m, q, a[N], L[50], R[50];
struct Hash {
	vector <int> a;
	void init() { a.clear(); }
	void add(int x) { a.push_back(x); }
	void gao() { sort(a.begin(), a.end()); a.erase(unique(a.begin(), a.end()), a.end()); }
	int get(int x) { return lower_bound(a.begin(), a.end(), x) - a.begin() + 1; }
}hs;

struct E {
	int op, x, y, z;
	E() {}
	E(int op, int x, int y, int z) : op(op), x(x), y(y), z(z) {}
}e[N]; 

inline int lowbit(int x) { return x & (-x); }

struct SEG {
	struct node {
		int ls, rs, sum;
		void init() { ls = rs = sum = 0; }
	}t[N * 50];
	int rt[N], tot;
	int newnode() {
		++tot;
		t[tot].init();
		assert(tot < N * 50);
		return tot;
	}
	void init() { memset(rt, 0, sizeof rt); tot = 0; t[0].init(); }
	void update(int &rt, int l, int r, int pos, int v) {
		if (!rt) rt = newnode();
		t[rt].sum += v;
		if (l == r) return;
		int mid = (l + r) >> 1;
		if (pos <= mid) update(t[rt].ls, l, mid, pos, v);
		else update(t[rt].rs, mid + 1, r, pos, v);
	}
	void update(int x, int pos, int v) {
		for (int i = x; i <= n; i += lowbit(i)) {
			update(rt[i], 1, m, pos, v);
		}
	}
	int query(int l, int r, int k) {
		if (l == r) return l;
		int mid = (l + r) >> 1;
		int lsum = 0, rsum = 0;
		for (int i = 1; i <= *L; ++i) lsum += t[t[L[i]].ls].sum;
		for (int i = 1; i <= *R; ++i) rsum += t[t[R[i]].ls].sum;
		if (rsum - lsum >= k) {
			for (int i = 1; i <= *L; ++i) L[i] = t[L[i]].ls;
			for (int i = 1; i <= *R; ++i) R[i] = t[R[i]].ls;
			return query(l, mid, k);
		} else {
			for (int i = 1; i <= *L; ++i) L[i] = t[L[i]].rs;
			for (int i = 1; i <= *R; ++i) R[i] = t[R[i]].rs;
			return query(mid + 1, r, k - (rsum - lsum));
		}
	}
}seg;

int main() {
	int _T; scanf("%d", &_T);
	while (_T--) {
		scanf("%d%d", &n, &q);
		hs.init();
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			hs.add(a[i]);
		}
		for (int i = 1, x, y, z; i <= q; ++i) {   
			static char op[10];
			scanf("%s", op);
			if (*op == 'Q') {
				scanf("%d%d%d", &x, &y, &z);
				e[i] = E(0, x, y, z);
			} else { 
				scanf("%d%d", &x, &y);    
				e[i] = E(1, x, y, 0); 
				hs.add(y);
			}
		}
		hs.gao(); m = hs.a.size();  
		for (int i = 1; i <= n; ++i) a[i] = hs.get(a[i]);
		for (int i = 1; i <= q; ++i) if (e[i].op == 1) e[i].y = hs.get(e[i].y);	
		seg.init();   
		for (int i = 1; i <= n; ++i) { 
			seg.update(i, a[i], 1);
		}
		for (int i = 1; i <= q; ++i) { 
			if (e[i].op == 0) { 
				*L = *R = 0; --e[i].x;
				for (int j = e[i].x; j; j -= lowbit(j)) {
					L[++*L] = seg.rt[j]; 
				}
				for (int j = e[i].y; j; j -= lowbit(j)) {
					R[++*R] = seg.rt[j];
				}
				printf("%d\n", hs.a[seg.query(1, m, e[i].z) - 1]); 
			} else {
				seg.update(e[i].x, a[e[i].x], -1);
				a[e[i].x] = e[i].y;
				seg.update(e[i].x, a[e[i].x], 1);
			}
		}
	}
	return 0;
}

