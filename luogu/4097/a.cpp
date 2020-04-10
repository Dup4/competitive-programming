#include <bits/stdc++.h>
using namespace std;
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
typedef double db;
const db INF = 2e18;
const db eps = 1e-10;
int sgn(db x) { if (fabs(x) < eps) return 0; return x < 0 ? -1 : 1; }
const int N = 1e5 + 10;
db K[N], B[N];

struct point {
    db x, y; int id;
    point(db _x = 0, db _y = 0, int id = 0) : x(_x), y(_y), id(id) {}
};
 
// upHull enables you to do the following two operations in amortized O(log n) time:
// 1. Insert a pair (a_i, b_i) into the structure
// 2. For any value of x, query the maximum value of a_i * x + b_i
// All values a_i, b_i, and x can be positive or negative.
struct UpHull {
    struct segment {
        point p;
        mutable point next_p;
        segment(point _p = {0, 0}, point _next_p = {0, 0}) : p(_p), next_p(_next_p) {}
        bool operator < (const segment &other) const {
            // Sentinel value indicating we should binary search the set for a single x-value.
            if (sgn(p.y - INF) == 0)
            	return sgn(p.x * (other.next_p.x - other.p.x) - (other.p.y - other.next_p.y)) <= 0;
            return make_pair(p.x, p.y) < make_pair(other.p.x, other.p.y);
        }
    };
    set<segment> segments;
	void init() { segments.clear(); }
    int size() const { return segments.size(); }
    set<segment>::iterator prev(set<segment>::iterator it) const { return it == segments.begin() ? it : --it; }
    set<segment>::iterator next(set<segment>::iterator it) const { return it == segments.end() ? it : ++it; }
//    static db floor_div(db a, db b) { return a / b - ((a ^ b) < 0 && a % b != 0); }
    static db floor_div(db a, db b) { return a * 1.0 / b; }
	static bool bad_middle(const point &a, const point &b, const point &c) {
        // This checks whether the x-value where b beats a comes after the x-value where c beats b. It's fine to round
        // down here if we will only query integer x-values. (Note: plain C++ division rounds toward zero)
        return sgn(floor_div(a.y - b.y, b.x - a.x) - floor_div(b.y - c.y, c.x - b.x)) >= 0;
    }
    bool bad(set<segment>::iterator it) const {
        return it != segments.begin() && next(it) != segments.end() && bad_middle(prev(it)->p, it->p, next(it)->p);
    }
    void insert(const point &p) {
        set<segment>::iterator next_it = segments.lower_bound(segment(p));
        if (next_it != segments.end() && p.x == next_it->p.x)
            return;
        if (next_it != segments.begin()) {
            set<segment>::iterator prev_it = prev(next_it);
            if (p.x == prev_it->p.x)
                segments.erase(prev_it);
            else if (next_it != segments.end() && bad_middle(prev_it->p, p, next_it->p))
                return;
        }
        // Note we need the segment(p, p) here for the single x-value binary search.
        set<segment>::iterator it = segments.insert(next_it, segment(p, p));
        while (bad(prev(it)))
            segments.erase(prev(it));
        while (bad(next(it)))
            segments.erase(next(it));
        if (it != segments.begin())
            prev(it)->next_p = it->p;
        if (next(it) != segments.end())
            it->next_p = next(it)->p;
    }
    void insert(db a, db b, int id) { insert(point(a, b, id)); }
    // Queries the maximum value of ax + b.
    int query(db x) {
		if (size() == 0) return 0;
        set<segment>::iterator it = segments.upper_bound(segment(point(x, INF)));
		return it->p.id;
      //  return it->p.x * x + it->p.y;
    }
};

struct SEG {
	UpHull t[N << 2];
	void build(int id, int l, int r) {
		t[id].init();
		if (l == r) return;
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
	}
	void update(int id, int l, int r, int ql, int qr, db k, db b, int pos) {
		if (l >= ql && r <= qr) {
			t[id].insert(k, b, pos);
			return;
		}
		int mid = (l + r) >> 1;
		if (ql <= mid) update(id << 1, l, mid, ql, qr, k, b, pos);
		if (qr > mid) update(id << 1 | 1, mid + 1, r, ql, qr, k, b, pos);
	}
	void chmax(int &a, int b, int x) {
		if (!a || !b) a |= b;
		else if (K[b] * x + B[b] > K[a] * x + B[a])
			a = b;
	}
	int query(int id, int l, int r, int x) {
		int pos = t[id].query(x);
		if (l == r) return pos;
		int mid = (l + r) >> 1;
		if (x <= mid) chmax(pos, query(id << 1, l, mid, x), x);
		else chmax(pos, query(id << 1 | 1, mid + 1, r, x), x);
		return pos;
	}
}seg;

int main() {
	int q, ans, tot;
	while(scanf("%d", &q) != EOF) {
		tot = 0;
		int n = 100000;
		int op, x[2], y[2];
		int mod = 39989;
		ans = 0;
		seg.build(1, 1, n);
		for (int _q = 1; _q <= q; ++_q) {
			scanf("%d", &op);
			switch(op) {
				case 0 :
					scanf("%d", x);
					x[0] = (x[0] + ans - 1) % mod + 1;
					printf("%d\n", ans = seg.query(1, 1, n, x[0]));
					break;
				case 1 :
					for (int i = 0; i < 2; ++i) {
						scanf("%d%d", x + i, y + i);
						x[i] = (x[i] + ans - 1) % mod + 1;
						y[i] = (y[i] + ans - 1) % 1000000000 + 1;
					}
					if (x[0] > x[1]) {
						swap(x[0], x[1]);
						swap(y[0], y[1]);
					}
					++tot;
					K[tot] = 1.0 * (y[0] - y[1]) / (x[0] - x[1]);
					B[tot] = y[0] - K[tot] * x[0];
					seg.update(1, 1, n, x[0], x[1], K[tot], B[tot], tot);
					break;
			}
		}
	} 
	return 0;
}
