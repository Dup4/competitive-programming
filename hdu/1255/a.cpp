#include <bits/stdc++.h>
using namespace std;
using db = double;
using pII = pair<int, int>;
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
#define fi first
#define se second
const int N = 2e5 + 20;
int n;

namespace RectangularAreaUnion {
	int m;
	struct E {
		db l, r, h; int d;
		E() {}
		E(db l, db r, db h, int d) : l(l), r(r), h(h), d(d) {}
		bool operator < (const E &other) const { if (h != other.h) return h < other.h; return d > other.d; }
	}e[N << 1];
	struct Hash {
		vector <db> a;
		db& operator[](int x) { return a[x - 1]; }
		int size() { return a.size(); }
		void init() { a.clear(); }
		void add(db x) { a.push_back(x); }
		void gao() { sort(a.begin(), a.end()); a.erase(unique(a.begin(), a.end()), a.end()); }
		int get(db x) { return lower_bound(a.begin(), a.end(), x) - a.begin() + 1; }	
	}hs;
	struct SEG {
		struct node {
			int cnt; db len[3];
			node() { cnt = 0; memset(len, 0, sizeof len); }
		}t[N << 2];
		void build(int id, int l, int r) {
			t[id] = node();
			if (l == r) return;
			int mid = (l + r) >> 1;
			build(id << 1, l, mid);
			build(id << 1 | 1, mid + 1, r);
		}
		void up(int id, int l, int r) {
			if (t[id].cnt >= 2) {
				t[id].len[2] = t[id].len[1] = hs[r] - hs[l - 1];
			} else if (t[id].cnt == 1) {
				t[id].len[1] = hs[r] - hs[l - 1];
				if (l == r) t[id].len[2] = 0;
				else t[id].len[2] = t[id << 1].len[1] + t[id << 1 | 1].len[1];
			} else {
				if (l == r) t[id].len[1] = t[id].len[2] = 0;
				else {
					t[id].len[1] = t[id << 1].len[1] + t[id << 1 | 1].len[1];
					t[id].len[2] = t[id << 1].len[2] + t[id << 1 | 1].len[2];
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
	db gao() {
		hs.init();
		m = 0;
		for (int i = 1; i <= n; ++i) {
			db x1, y1, x2, y2;
			scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
			e[++m] = E(x1, x2, y1, 1);
			e[++m] = E(x1, x2, y2, -1);
			hs.add(x1); hs.add(x2);
		}
		sort(e + 1, e + 1 + m);
		hs.gao();
		int _n = hs.size();
		seg.build(1, 1, _n);
		db res = 0;
		for (int i = 1; i < m; ++i) {
			int l = hs.get(e[i].l) + 1;
			int r = hs.get(e[i].r);
			seg.update(1, 1, _n, l, r, e[i].d);
			res += seg.t[1].len[2] * (e[i + 1].h - e[i].h);	
		}
		return res;
	}	
}

int main() {
	int _T; scanf("%d", &_T);
	while (_T--) {
		scanf("%d", &n);
	   	printf("%.2f\n", RectangularAreaUnion::gao());
	}
	return 0;
}
