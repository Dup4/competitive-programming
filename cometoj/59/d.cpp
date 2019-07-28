#include <bits/stdc++.h>
using namespace std;

#define N 200010
int n, k, X[N << 1], Y[N << 1];
vector <vector<int>> add, del;

struct node {
	int x[2], y[2];
	node() {}
	void scan() {
		scanf("%d%d", x, y);
		x[1] = x[0] + k;
		y[1] = y[0] + k;
		for (int i = 0; i < 2; ++i) {
			X[++X[0]] = x[i];
			Y[++Y[0]] = y[i];
		}
	} 
}a[N];

void Hash(int *x) {
	sort(x + 1, x + 1 + x[0]);
	x[0] = unique(x + 1, x + 1 + x[0]) - x - 1;
}

struct SEG {
	struct node {
		int Max, lazy;
		node() {
			Max = 0;
			lazy = 0;
		}
		void add(int x) {
			Max += x;
			lazy += x;
		}
		node operator + (const node &other) const {
			node res = node();
			res.Max = max(Max, other.Max);
			return res;
		}
	}t[N << 3];
	void build(int id, int l, int r) {
		t[id] = node();
		if (l == r) return;
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
	}
	void pushdown(int id) {
		int &lazy = t[id].lazy;
		if (!lazy) return;
		t[id << 1].add(lazy);
		t[id << 1 | 1].add(lazy);
		lazy = 0;
	}
	void update(int id, int l, int r, int ql, int qr, int x) {
		if (l >= ql && r <= qr) {
			t[id].add(x);
			return;
		}
		int mid = (l + r) >> 1;
		pushdown(id);
		if (ql <= mid) update(id << 1, l, mid, ql, qr, x);
		if (qr > mid) update(id << 1 | 1, mid + 1, r, ql, qr, x);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
}seg;

int main() {
	while (scanf("%d%d", &n, &k) != EOF) {
		X[0] = Y[0] = 0; 
		for (int i = 1; i <= n; ++i) {
			a[i].scan();
		}
		Hash(X); Hash(Y);
		add.clear(); add.resize(X[0] + 10);
		del.clear(); del.resize(X[0] + 10);
		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j < 2; ++j) {
				a[i].x[j] = lower_bound(X + 1, X + 1 + X[0], a[i].x[j]) - X;
				a[i].y[j] = lower_bound(Y + 1, Y + 1 + Y[0], a[i].y[j]) - Y; 
			}
			add[a[i].x[0]].push_back(i);
			del[a[i].x[1]].push_back(i);
		}
		int res = 0;
		seg.build(1, 1, Y[0]);
		for (int i = 1; i <= X[0]; ++i) {
			for (auto it : add[i]) {
				seg.update(1, 1, Y[0], a[it].y[0], a[it].y[1], 1);
			}
			res = max(res, seg.t[1].Max);
			for (auto it : del[i]) {
				seg.update(1, 1, Y[0], a[it].y[0], a[it].y[1], -1);
			}	
		} 
		printf("%d\n", res);
	}
	return 0;
}
