#include <bits/stdc++.h>
using namespace std;
typedef double db;
const db INF = 2e18;
const db eps = 1e-10;
int sgn(db x) {
    if (fabs(x) < eps)
        return 0;
    return x < 0 ? -1 : 1;
}

struct point {
    db x, y;
    point(db _x = 0, db _y = 0) : x(_x), y(_y) {}
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
        bool operator<(const segment &other) const {
            // Sentinel value indicating we should binary search the set for a single x-value.
            if (sgn(p.y - INF) == 0)
                return sgn(p.x * (other.next_p.x - other.p.x) - (other.p.y - other.next_p.y)) <= 0;
            return make_pair(p.x, p.y) < make_pair(other.p.x, other.p.y);
        }
    };
    set<segment> segments;
    void clear() {
        segments.clear();
    }
    int size() const {
        return segments.size();
    }
    set<segment>::iterator prev(set<segment>::iterator it) const {
        return it == segments.begin() ? it : --it;
    }
    set<segment>::iterator next(set<segment>::iterator it) const {
        return it == segments.end() ? it : ++it;
    }
    //    static db floor_div(db a, db b) { return a / b - ((a ^ b) < 0 && a % b != 0); }
    static db floor_div(db a, db b) {
        return a * 1.0 / b;
    }
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
        while (bad(prev(it))) segments.erase(prev(it));
        while (bad(next(it))) segments.erase(next(it));
        if (it != segments.begin())
            prev(it)->next_p = it->p;
        if (next(it) != segments.end())
            it->next_p = next(it)->p;
    }
    void insert(db a, db b) {
        insert(point(a, b));
    }
    // Queries the maximum value of ax + b.
    db query(db x) const {
        if (size() == 0)
            return -INF;
        set<segment>::iterator it = segments.upper_bound(segment(point(x, INF)));
        return it->p.x * x + it->p.y;
    }
};

int main() {
    int q;
    UpHull upHull;
    upHull.clear();
    while (scanf("%d", &q) != EOF) {
        char op[20];
        db k, b;
        int x;
        for (int _q = 1; _q <= q; ++_q) {
            scanf("%s", op + 1);
            switch (op[1]) {
                case 'P':
                    scanf("%lf%lf", &b, &k);
                    upHull.insert(k, b - k);
                    break;
                case 'Q':
                    scanf("%d\n", &x);
                    printf("%.0f\n", (floor)((max(0.0, upHull.query(x)) / 100)));
                    break;
            }
        }
    }
    return 0;
}
