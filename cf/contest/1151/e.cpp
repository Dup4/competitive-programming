#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
int n;
vector <int> vec[N];
int vis[N];

struct SEG {
	struct node {
		int sum, lazy, cnt;
		node () {}
		node (int sum, int lazy) : sum(sum), lazy(lazy) {
			cnt = 0;
		}
		void add(int x) {
			sum += cnt * x; 
			lazy += x; 
		}
		node operator + (const node &other) const {
			node res = node();
			res.cnt = cnt + other.cnt;
			res.sum = sum + other.sum;
			return res;
		}
	}t[N << 2];
	void build(int id, int l, int r) {
		if (l == r) {
			t[id] = node();
			t[id].cnt = 1;
			return;
		}
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	void pushdown(int id) {
		int &lazy = t[id].lazy;
		if (!lazy) {
			return;
		}
		t[id << 1].add(lazy);
		t[id << 1 | 1].add(lazy);
		lazy = 0;
	}
	void update(int id, int l, int r, int ql, int qr, int v) {
		if (ql > qr) {
			return;
		}
		if (l >= ql && r <= qr) {
			t[id].add(v);
			return;
		}
		int mid = (l + r) >> 1;
		pushdown(id);
		if (ql <= mid) update(id << 1, l, mid, ql, qr, v);
		if (qr > mid) update(id << 1 | 1, mid + 1, r, ql, qr, v);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	ll query(int id, int l, int r, int ql, int qr) {
		if (ql > qr) {
			return 0;
		}
		if (l >= ql && r <= qr) {
			return t[id].sum;
		}
		int mid = (l + r) >> 1;
		pushdown(id);
		ll res = 0;
		if (ql <= mid) res += query(id << 1, l, mid, ql, qr);
		if (qr > mid) res += query(id << 1 | 1, mid + 1, r, ql, qr);
		return res;
	}
}seg;

void init() {
	memset(vis, 0, sizeof vis);
	for (int i = 1; i <= n; ++i) {
		vec[i].clear();
	}
	seg.build(1, 1, n);
}
int main() {
	while (scanf("%d", &n) != EOF) {
		init();
		for (int i = 1, x; i <= n; ++i) {
			scanf("%d", &x);
			vis[i] = x;
			vec[x].push_back(i); 
		}
		if (n == 1) {
			puts("1");
			continue;
		}
		for (int i = 1; i <= n; ++i) if (!vec[i].empty()) {
			sort(vec[i].begin(), vec[i].end());
		}
		ll res = 0;
		for (int i = n; i >= 1; --i) {
			for (auto it : vec[i]) {
				if (it == 1) {
					if (vis[2] > i) { 
						seg.update(1, 1, n, i, vis[2] - 1, 1); 
					} else if (vis[2] <= i) {
						seg.update(1, 1, n, i, n, 1);
					}
				} else if (it == n) {
					if (vis[n - 1] >= i) {
						seg.update(1, 1, n, i, vis[n - 1] - 1, 1);
					} else {
						seg.update(1, 1, n, i, n, 1);
					}
				} else {
					int x = vis[it - 1], y = vis[it + 1];
					if (x == i) {
						if (y == i) {
							
						}
						if (y >= i) {
							seg.update(1, 1, n, y, n, -1);
						}
					} else if (y == i) {
						seg.update(1, 1, n, i, i, 1);
						if (x > i) {
							seg.update(1, 1, n, x, n, -1);
						}
					} else {
						if (x > y) swap(x, y);
						if (x > i) {
							seg.update(1, 1, n, i, x - 1, 1);
							seg.update(1, 1, n, y, n, -1); 
						} else if (y > i) {
							seg.update(1, 1, n, i, y - 1, 1);
						}
					}
				}
			}
			res += seg.query(1, 1, n, 1, n);
		}
		printf("%lld\n", res);
	}
	return 0;
}
