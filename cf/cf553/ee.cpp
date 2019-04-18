#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
int n;
vector <int> vec[N];
int vis[N];

struct SEG {
	struct node {
		ll sum, lazy;
		int cnt;
		node () {
			sum = lazy = cnt = 0;
		}
		node (ll sum, ll lazy) : sum(sum), lazy(lazy) {
			cnt = 0;
		}
		void add(int x) {
			sum += 1ll * x * cnt; 
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
		ll &lazy = t[id].lazy;
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
	vis[0] = vis[n + 1] = -1;
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
		ll res = 0;
		for (int i = n; i >= 1; --i) if (!vec[i].empty()) { 
			for (int last = vec[i][0], j = 0, sze = (int)vec[i].size(); j < sze; ++j) {
				if (j == sze - 1 || vec[i][j] != vec[i][j + 1] - 1) {   
					int l = last - 1, r = vec[i][j] + 1;
					if (vis[l] > vis[r]) swap(l, r);
					if (vis[l] > i) {
						seg.update(1, 1, n, i, vis[l] - 1, 1);
						seg.update(1, 1, n, vis[r], n, -1);
					} else if (vis[r] > i) {
						seg.update(1, 1, n, i, vis[r] - 1, 1);
					} else {
						seg.update(1, 1, n, i, n, 1);
					}
					if (j != sze - 1) {
						last = vec[i][j + 1];
					}
				}
			}
			//cout << i << " " << seg.query(1, 1, n, i, n) << endl;
			res += seg.query(1, 1, n, i, n);
		}
		printf("%lld\n", res);
	}
	return 0;
}

