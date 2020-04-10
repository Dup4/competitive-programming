#include <cstdio>
#include <algorithm>
#include <iostream>
#include <set>
using namespace std;
//#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
//void err() { cout << "\033[39;0m" << endl; } 
//template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
typedef long long ll;
typedef long long db;
const int N = 1e4 + 10;
const ll INF = 1e18;
int n, m, a[N];
int sgn(db x) { if (x == 0) return 0; return x < 0 ? -1 : 1; }


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
}upHull[5010];

//struct LineContainer {
//    struct node {
//        ll a, b, x;
//        node() {}
//        node(ll a, ll b, ll x) : a(a), b(b), x(x) {}
//    }t[N * 3]; int l, r, pos;
//    void init() {
//        l = N * 3 - 10, r = l - 1;
//        pos = r;
//    }
//    void insert(ll a, ll b) {
//        if (r < l) {
//            t[--l] = node(a, b, INF);
//            return;
//        }
//        ll x = -INF;
//        while (l <= r) {
//            node tmp = t[l];
//            ll cross = (tmp.b - b) / (a - tmp.a);
//            if (cross <= x) break;
//            if (cross < t[l].x) {
//                x = cross;
//                break;
//            } else {
//                x = t[l].x;
//                ++l;
//            }
//        }
//        t[--l] = node(a, b, x);
//    }
//    ll query(ll x) {
//		if (l > r) return -INF;
//        while (l < pos && t[pos - 1].x >= x) --pos;
//        return 1ll * t[pos].a * x + t[pos].b;
//    }
//};

int main() {
	int _T; scanf("%d", &_T);
	for (int kase = 1; kase <= _T; ++kase) {
		printf("Case %d: ", kase);
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		sort(a + 1, a + 1 + n);
		for (int i = 0; i <= m; ++i) upHull[i].clear();
		upHull[0].insert(a[1] * 2, -1ll * a[1] * a[1]);
	//	lc[0].insert(a[1] * 2, -1ll * a[1] * a[1]);
		ll res = INF;
		for (int i = 1; i <= n; ++i) {
			for (int j = m; j >= 1; --j) {
				ll now = upHull[j - 1].query(a[i]) - 1ll * a[i] * a[i];
		//		ll now = lc[j - 1].query(a[i]) - 1ll * a[i] * a[i];
		//		dbg(i, j, now);
				if (i == n) res = min(res, -now); 
				else upHull[j].insert(a[i + 1] * 2, now - 1ll * a[i + 1] * a[i + 1]);
			}
		}
		printf("%lld\n", res);
	}
	return 0;
}
