#include <bits/stdc++.h>
using namespace std;
typedef long long db;
const int N = 1e5 + 10, M = 1e4 + 10;
const db INF = 1e18;
int n, a[N], f[N], cnt[M]; 
db g[N];
inline int sgn(db x) { if (x == 0) return 0; return x < 0 ? -1 : 1; }

// upHull enables you to do the following two operations in amortized O(log n) time:
// 1. Insert a pair (a_i, b_i) into the structure
// 2. For any value of x, query the maximum value of a_i * x + b_i
// All values a_i, b_i, and x can be positive or negative.
struct UpHull {
	struct Point {
	    db x, y; 
	    Point(db _x = 0, db _y = 0) : x(_x), y(_y) {}
	};
    struct segment {
        Point p;
        mutable Point next_p;
        segment(Point _p = {0, 0}, Point _next_p = {0, 0}) : p(_p), next_p(_next_p) {}
        bool operator < (const segment &other) const {
            // Sentinel value indicating we should binary search the set for a single x-value.
            if (sgn(p.y - INF) == 0)
            	return sgn(p.x * (other.next_p.x - other.p.x) - (other.p.y - other.next_p.y)) <= 0;
            return sgn(p.x - other.p.x) == 0 ? sgn(p.y - other.p.y) < 0 : p.x < other.p.x;
        }
    };
    set<segment> segments;
	void clear() { segments.clear(); }
    int size() const { return segments.size(); }
    set<segment>::iterator prev(set<segment>::iterator it) const { return it == segments.begin() ? it : --it; }
    set<segment>::iterator next(set<segment>::iterator it) const { return it == segments.end() ? it : ++it; }
    //double类型使用
	//static db floor_div(db a, db b) { return a / b; }
	static db floor_div(db a, db b) { return a / b - ((a ^ b) < 0 && a % b != 0); }
	static bool bad_middle(const Point &a, const Point &b, const Point &c) {
        // This checks whether the x-value where b beats a comes after the x-value where c beats b. It's fine to round
        // down here if we will only query integer x-values. (Note: plain C++ division rounds toward zero)
        return sgn(floor_div(a.y - b.y, b.x - a.x) - floor_div(b.y - c.y, c.x - b.x)) >= 0;
    }
    bool bad(set<segment>::iterator it) const {
        return it != segments.begin() && next(it) != segments.end() && bad_middle(prev(it)->p, it->p, next(it)->p);
    }
    void insert(const Point &p) {
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
    void insert(db a, db b) { insert(Point(a, b)); }
    // Queries the maximum value of ax + b.
    db query(db x) {
		if (size() == 0) return -INF;
        set<segment>::iterator it = segments.upper_bound(segment(Point(x, INF)));
      	return it->p.x * x + it->p.y;
    }
}upHull[N];



int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", a + i);
	for (int i = 1; i <= n; ++i) {
		++cnt[a[i]];
		f[i] = cnt[a[i]];
	}
	db res = 0;
	for (int i = 1; i <= n; ++i) {
		g[i] = res + a[i];
	    g[i] = max(g[i], upHull[a[i]].query(f[i]) + 1ll * f[i] * f[i] * a[i]);
		upHull[a[i]].insert(-2ll * a[i] * (f[i] - 1), g[i - 1] + 1ll * a[i] * (f[i] - 1) * (f[i] - 1));
		res = max(res, g[i]);
	}
	printf("%lld\n", res);
	return 0;
}
