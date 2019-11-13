#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;
const int INF = 0x3f3f3f3f;

int n, m, q;
vector<vector<int> >G;
int a[N], rk[N], remind[N];


struct SEG {
	struct node {
		int Min;
		int lazy;

		node() {}

		node(int _Min, int _lazy) {
			Min = _Min;
			lazy = _lazy;
		}

		void up(int x) {
			Min += x;
			lazy += x;
		}
	}t[N << 2];


	void down(int id) {
		int &lazy = t[id].lazy;
		if (lazy) {
			t[id << 1].up(lazy);
			t[id << 1 | 1].up(lazy);
			lazy = 0;
		}	
	}

	void pushup(int id) {
		t[id].Min = min(t[id << 1].Min, t[id << 1 |1].Min);
	}

	void build(int id, int l, int r) {
		t[id] = {0, 0};
		if (l == r) {
			t[id].Min = remind[l];
			t[id].lazy = 0;
			return ;
		}
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
		pushup(id);
	}

	void modify(int id, int l, int r, int ql, int qr, int v) {
		if (ql > qr) return ;
		if (l >= ql && r <= qr) {
			t[id].up(v);
			return ;
		}
		int mid = (l + r) >> 1;
		down(id);
		if (ql <= mid) modify(id << 1, l, mid, ql, qr, v);
		if (qr > mid) modify(id << 1 | 1, mid + 1, r, ql, qr, v);
		pushup(id);
	}

	int query(int id, int l, int r, int ql, int qr) {
		if (l >= ql && r <= qr) return t[id].Min;
		int mid = (l + r);
		down(id);
		int res = INF;
		if (ql <= mid) res = min(res, query(id << 1, l, mid, ql, qr));
		if (qr > mid) res = min(res, query(id << 1 | 1, mid + 1, r, ql, qr));
		return res;
	}
}seg;

int main() {
	while (scanf("%d %d %d", &n, &m, &q) != EOF) {
		G.clear();
		G.resize(m + 1);
		rk[1] = 1;
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			if (a[i] > a[1]) {
				rk[1]++;
			}
		}
		for (int i = 1, r, b; i <= m; ++i) {
			scanf("%d", &r);
			rk[i + 1] = rk[i];
			for (int j = 1; j <= r; ++j) {
				scanf("%d", &b);
				G[i].push_back(b);
				if (b > a[1]) {
					rk[i + 1]++;
				}
			}
			remind[i] = n - r - rk[i];
		}
		seg.build(1, 1, m);
		for (int _q = 1, x, y, z; _q <= q; ++_q) {
			scanf("%d %d %d", &x, &y, &z);
			int pre = G[x][y - 1], now = z;
			if (pre < a[1] && now > a[1]) {
				seg.modify(1, 1, m, x + 1, m, -1);
			}
			if (pre > a[1] && now < a[1]) {
				seg.modify(1, 1, m, x + 1, m, 1);
			}
			int rank = seg.t[1].Min;
			puts(rank < 0 ? "0" : "1");
			G[x][y - 1] = z;
		}
	}
	return 0;
}
