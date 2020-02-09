#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 10, INF = 0x3f3f3f3f;
int n, q, a[N];

struct SEG {
	//+ < 取Min, 询问Max  - > 取Max, 询问Min 修改build初始化叶子结点
	static const int INF = 0x3f3f3f3f;
	static bool cmp(int x, int y) { return x < y; }
	static int get(int x, int y) { return cmp(x, y) ? y : x; }
	struct TAG {
		int v[2], cnt;
		TAG() {}
		void init() { v[0] = v[1] = -INF, cnt = 0;  } 
		TAG operator + (const TAG &other) const {
			TAG res; res.init();
			if (v[0] == other.v[0]) {
				res.v[0] = v[0];
				res.cnt = cnt + other.cnt;
				res.v[1] = get(v[1], other.v[1]);
			} else {
				if (cmp(v[0], other.v[0])) {
					res = other;
					res.v[1] = get(other.v[1], v[0]);
				} else {
					res = *this;
					res.v[1] = get(v[1], other.v[0]);
				}
			}	
			return res;
		}
	};
	struct node {
		ll sum; int lazy; 
	   	TAG tag; 
		node() { tag.init(); sum = 0; lazy = INF; }
		void up(int _lazy) {
		    if (cmp(_lazy, tag.v[0]) == 0) return; 
			sum += 1ll * tag.cnt * (_lazy - tag.v[0]); 
			tag.v[0] = _lazy;
			lazy = _lazy;
		}
		node operator + (const node &other) const {
			node res = node();
			res.sum = sum + other.sum; 
			res.tag = tag + other.tag;
			return res;
		}
	}t[N << 2], res; 
	void build(int id, int l, int r) {
		t[id] = node();
		if (l == r) {
			t[id].tag.cnt = 1;
			t[id].tag.v[0] = a[l];
			t[id].sum = a[l]; 
			return;
		}
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	void pushdown(int id) {
		int &lazy = t[id].lazy;
		if (lazy == INF) return;
		t[id << 1].up(lazy);
		t[id << 1 | 1].up(lazy);
		lazy = INF;
	}
	void update(int id, int l, int r, int ql, int qr, int x) {
		if (cmp(x, t[id].tag.v[0]) == 0) return; 
		if (l == r) {
			x = cmp(x, t[id].tag.v[0]) ? x : t[id].tag.v[0];
			t[id].sum = x;
			t[id].tag.v[0] = x;
			t[id].tag.v[1] = -INF;
			return;
		} 
		if (l >= ql && r <= qr && cmp(x, t[id].tag.v[0]) && cmp(t[id].tag.v[1], x)) {
			t[id].up(x);
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
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &q);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
		}
		seg.build(1, 1, n);
		int op, x, y, t;
		while (q--) {
			scanf("%d%d%d", &op, &x, &y);
			if (!op) {
				scanf("%d", &t);
				seg.update(1, 1, n, x, y, t);
			} else {
				seg.res = SEG::node();
				seg.query(1, 1, n, x, y);
				printf("%lld\n", (op == 1 ? seg.res.tag.v[0] : seg.res.sum));
			}
		}
	}
	return 0;
}
