#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int n;

namespace RectangularPerimeterUnion {
	int cor[2][N][2], m;
	struct E {
		int l, r, h, d;
		E() {}
		E(int l, int r, int h, int d) : l(l), r(r), h(h), d(d) {}
		bool operator < (const E &other) const { if (h != other.h) return h < other.h; return d > other.d; }
	}e[N << 1];
	struct Hash {
		vector <int> a;
		int operator[](int x) { return a[x - 1]; }
		int size() { return a.size(); }
		void init() { a.clear(); }
		void add(int x) { a.push_back(x); }
		void gao() { sort(a.begin(), a.end()); a.erase(unique(a.begin(), a.end()), a.end()); }
		int get(int x) { return lower_bound(a.begin(), a.end(), x) - a.begin() + 1; }	
	}hs;
	struct SEG {
		struct node {
			int cnt, len;
			node() { cnt = len = 0; }
		}t[N << 2];
		void build(int id, int l, int r) {
			t[id] = node();
			if (l == r) return;
			int mid = (l + r) >> 1;
			build(id << 1, l, mid);
			build(id << 1 | 1, mid + 1, r);
		}
		void up(int id, int l, int r) {
			if (t[id].cnt > 0) {
				t[id].len = hs[r] - hs[l - 1];
			} else {
				if (l == r) {
					t[id].len = 0;
				} else {
					t[id].len = t[id << 1].len + t[id << 1 | 1].len;
				}
			}
		}
		void update(int id, int l, int r, int ql, int qr, int v) {
			if (ql > qr) return;
			if (l >= ql && r <= qr) {
				t[id].cnt += v;
				up(id, l, r);
				return;
			}
			int mid = (l + r) >> 1;
			if (ql <= mid) update(id << 1, l, mid, ql, qr, v);
			if (qr > mid) update(id << 1 | 1, mid + 1, r, ql, qr, v);
			up(id, l, r);
		}
	}seg;
	int calc(int p) {
		hs.init();
		for (int i = 1; i <= n; ++i) {
			hs.add(cor[p][i][0]);
			hs.add(cor[p][i][1]);
		}
		hs.gao();
		m = 0;
		for (int i = 1; i <= n; ++i) {
			int l = hs.get(cor[p][i][0]);
			int r = hs.get(cor[p][i][1]);
			e[++m] = E(l + 1, r, cor[p ^ 1][i][0], 1);
			e[++m] = E(l + 1, r, cor[p ^ 1][i][1], -1);
		}
		sort(e + 1, e + 1 + m);
		int _n = hs.size();
		seg.build(1, 1, _n);
		int last = 0;
		int res = 0;
		for (int i = 1; i <= m; ++i) {
			int l = e[i].l, r = e[i].r;
			seg.update(1, 1, _n, l, r, e[i].d);
			int now = seg.t[1].len;
			res += abs(now - last);
			last = now;
		}
		return res;
	}
	int gao() {
		for (int i = 1; i <= n; ++i) {
			scanf("%d%d%d%d", &cor[0][i][0], &cor[1][i][0], &cor[0][i][1], &cor[1][i][1]);
		}
		return calc(0) + calc(1);
	}
}

int main() {
	while (scanf("%d", &n) != EOF) printf("%d\n", RectangularPerimeterUnion::gao());
    return 0;
}
