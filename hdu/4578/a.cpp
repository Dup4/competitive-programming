#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10, MOD = 1e4 + 7;
int n, q;
struct SEG {
	struct node {
		int l, r;
		int sum[3], lazy[3]; 
		node() {} 
		node(int _l, int _r) {
			l = _l, r = _r;
			memset(sum, 0, sizeof sum);
			lazy[0] = 0, lazy[1] = 1, lazy[2] = -1; 
		}
	}t[N << 2];
	void pushup(int id) {
		for (int i = 0; i < 3; ++i) {
			t[id].sum[i] = (t[id << 1].sum[i] + t[id << 1 | 1].sum[i]) % MOD;
		}
	}
	
	//add
	void work1(node &r, int b) {
		int len = r.r - r.l + 1;  
		r.sum[2] = (r.sum[2] + (len * b % MOD * b % MOD * b % MOD) + (3 * b % MOD * b % MOD * r.sum[0] % MOD) + (3 * b % MOD * r.sum[1] % MOD)) % MOD;
		r.sum[1] = (r.sum[1] + (2 * b % MOD * r.sum[0] % MOD) + (len * b % MOD * b % MOD)) % MOD;
		r.sum[0] = (r.sum[0] + len * b % MOD) % MOD;
		r.lazy[0] = (r.lazy[0] + b) % MOD; 
	} 
	
	//mul
	void work2(node &r, int b) {
		r.sum[0] = (r.sum[0] * b) % MOD;
		r.sum[1] = (r.sum[1] * b % MOD * b) % MOD;
		r.sum[2] = (r.sum[2] * b % MOD * b % MOD * b) % MOD;
		r.lazy[0] = r.lazy[0] * b % MOD;
		r.lazy[1] = r.lazy[1] * b % MOD;
	} 
	
	//change
	void work3(node &r, int b) {
		int len = r.r - r.l + 1;
		r.sum[0] = len * b % MOD;
		r.sum[1] = r.sum[0] * b % MOD;
		r.sum[2] = r.sum[1] * b % MOD; 
		r.lazy[0] = 0; r.lazy[1] = 1;  
		r.lazy[2] = b;   
	} 
	
	void pushdown(int id) {
		if (t[id].l >= t[id].r) return; 
		if (~t[id].lazy[2]) {
			work3(t[id << 1], t[id].lazy[2]);
			work3(t[id << 1 | 1], t[id].lazy[2]); 
			t[id].lazy[2] = -1;  
		}
		if (t[id].lazy[1] != 1) {
			work2(t[id << 1], t[id].lazy[1]);
			work2(t[id << 1 | 1], t[id].lazy[1]);
			t[id].lazy[1] = 1; 
		}
		if (t[id].lazy[0]) {
			work1(t[id << 1], t[id].lazy[0]);
			work1(t[id << 1 | 1], t[id].lazy[0]);
			t[id].lazy[0] = 0; 
		}
	}
	
	void build(int id, int l, int r) {
		t[id] = node(l, r);
		if (l == r) return;
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
	}
	
	void update(int id, int l, int r, int vis, int val) {
		if (t[id].l >= l && t[id].r <= r) {
			if (vis == 1) work1(t[id], val); 
			else if (vis == 2) work2(t[id], val);
			else work3(t[id], val);   
			return;  
		}
		pushdown(id); 
		int mid = (t[id].l + t[id].r) >> 1;
		if (l <= mid) update(id << 1, l, r, vis, val);
		if (r > mid) update(id << 1 | 1, l, r, vis, val);  
		pushup(id);
	}
	
	int query(int id, int l, int r, int p) {
		if (t[id].l >= l && t[id].r <= r) return t[id].sum[p]; 
		int res = 0;
		pushdown(id); 
		int mid = (t[id].l + t[id].r) >> 1;
		if (l <= mid) res = (res + query(id << 1, l, r, p)) % MOD; 
		if (r > mid) res = (res + query(id << 1 | 1, l, r, p)) % MOD; 
		return res;
	}

}seg;

int main() {
	while (scanf("%d%d", &n, &q), n || q) {
		seg.build(1, 1, n);
		for (int i = 1, op, x, y, c; i <= q; ++i) {
			scanf("%d%d%d%d", &op, &x, &y, &c);
			if (op <= 3) seg.update(1, x, y, op, c); 
			else printf("%d\n", seg.query(1, x, y, c - 1));
		}
	}
	return 0;
}
