#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int n, q;
struct SEG {
	struct node {
		int Max, lazy;
		node() { Max = lazy = 0; }
		void up(int x) {
			Max += x;
			lazy += x;
		}
		node operator + (const node &other) const {
			node res = node();
			res.Max = max(Max, other.Max);
			return res;
		}
	}t[N << 2];
	void build(int id, int l, int r) {
		t[id] = node();
		if (l == r) return;
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
	}
	void down(int id) {
		int &lazy = t[id].lazy;
		if (lazy) {
			t[id << 1].up(lazy);
			t[id << 1 | 1].up(lazy);
			lazy = 0;
		}
	}
	void update(int id, int l, int r, int ql, int qr, int v) {
		if (l >= ql && r <= qr) {
			t[id].up(v);
			return;
		}
		int mid = (l + r) >> 1;
		down(id);
		if (ql <= mid) update(id << 1, l, mid, ql, qr, v);
		if (qr > mid) update(id << 1 | 1, mid + 1, r, ql, qr, v);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	int query(int id, int l, int r, int ql, int qr) {
		if (l >= ql && r <= qr) return t[id].Max;
		int mid = (l + r) >> 1;
		down(id);
		int res = 0;
		if (ql <= mid) res = max(res, query(id << 1, l, mid, ql, qr));
		if (qr > mid) res = max(res, query(id << 1 | 1, mid + 1, r, ql, qr));
		return res;
	}
}seg[4];

int main() {
	int id[] = {0, 0, 0, 1, 0, 2, 0, 3, 0};
	vector <vector<int>> vec;
	vec.resize(15);
	for (int i = 2; i <= 10; ++i) {
		int x = i;
		vec[i].clear();
		for (int j = 2; j <= x; ++j) {
			while (x % j == 0) {
				vec[i].push_back(j);
				x /= j;
			}
		}
	//	cout << i << endl;
	//	for (auto &it : vec[i])
	//		cout << it << " ";
	//	cout << endl;
	}
	while (scanf("%d%d", &n, &q) != EOF) {
		for (int i = 0; i < 4; ++i) seg[i].build(1, 1, n);
		char op[20]; int l, r, x;
		while (q--) {
			scanf("%s%d%d", op, &l, &r);
			if (op[1] == 'U') {
				scanf("%d", &x);
				for (auto &it : vec[x]) {
					seg[id[it]].update(1, 1, n, l, r, 1);
				}
			} else {
				int res = 0;
				for (int i = 0; i < 4; ++i) {
					res = max(res, seg[i].query(1, 1, n, l, r));
				}
				printf("ANSWER %d\n", res);
			}
		}	
	}
	return 0;
}
