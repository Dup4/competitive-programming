#include <bits/stdc++.h>
using namespace std;
#define dbg(x...)                             \
    do {                                      \
        cout << "\033[32;1m" << #x << " -> "; \
        err(x);                               \
    } while (0)
void err() {
    cout << "\033[39;0m" << endl;
}
template <class T, class... Ts>
void err(const T &arg, const Ts &...args) {
    cout << arg << ' ';
    err(args...);
}
typedef long long db;
typedef long long ll;
const db INF = 1e18;
const db eps = 1e-10;
const db PI = acos(-1.0);
int sgn(db x) {
    if (x == 0)
        return 0;
    return x < 0 ? -1 : 1;
}
const int N = 4e5 + 10;

// upHull enables you to do the following two operations in amortized O(log n) time:
// 1. Insert a pair (a_i, b_i) into the structure
// 2. For any value of x, query the maximum value of a_i * x + b_i
// All values a_i, b_i, and x can be positive or negative.
struct HULL {
    struct point {
        db x, y;
        point(db _x = 0, db _y = 0) : x(_x), y(_y) {}
    };
    struct segment {
        point p;
        mutable point next_p;
        int opt;
        segment(point _p = {0, 0}, point _next_p = {0, 0}, int opt = 0) : p(_p), next_p(_next_p), opt(opt) {}
        bool operator<(const segment &other) const {
            // Sentinel value indicating we should binary search the set for a single x-value.
            if (opt) {
                return sgn(p.x * (other.next_p.x - other.p.x) + p.y * (other.next_p.y - other.p.y)) <= 0;
            } else {
                return sgn(p.x - other.p.x) == 0 ? p.y < other.p.y : p.x < other.p.x;
                // make_pair(p.x, p.y) < make_pair(other.p.x, other.p.y);
            }
        }
    };
    set<segment> segments;
    void init() {
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
    static db floor_div(db a, db b) {
        return a / b - ((a ^ b) < 0 && a % b != 0);
    }
    // static db floor_div(db a, db b) { return a / b; }
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
    db query(db x, db y) {
        if (size() == 0)
            return -INF;
        db Max = 0;
        for (auto &it : segments) Max = max(Max, it.p.x * x + it.p.y * y);
        return Max;
        // set<segment>::iterator it = segments.upper_bound(segment(point(x, INF)));
        set<segment>::iterator it = segments.upper_bound(segment(point(x, y), point(0, 0), 1));
        return it->p.x * x + it->p.y * y;
    }
};

struct SEG {
    HULL upHull[N << 2], downHull[N << 2];
    void build(int id, int l, int r) {
        upHull[id].init();
        downHull[id].init();
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
    }
    void ins(int id, int l, int r, int pos, db x, db y) {
        upHull[id].insert(x, y);
        //	downHull[id].insert(x, -y);
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        if (pos <= mid)
            ins(id << 1, l, mid, pos, x, y);
        else
            ins(id << 1 | 1, mid + 1, r, pos, x, y);
    }
    db query(int id, int l, int r, int ql, int qr, db x, db y) {
        dbg(id, l, r, ql, qr);
        if (l >= ql && r <= qr) {
            if (y >= 0)
                return upHull[id].query(x, y);
            //		else return downHull[id].query(x, -y);
            else
                return 0;
        }
        dbg(id, l, r, ql, qr);
        int mid = (l + r) >> 1;
        db Max = -INF;
        if (ql <= mid)
            Max = max(Max, query(id << 1, l, mid, ql, qr, x, y));
        if (qr > mid)
            Max = max(Max, query(id << 1 | 1, mid + 1, r, ql, qr, x, y));
        return Max;
    }
} seg;

int main() {
    ll lst = 0;
    int n = 0;
    int m = 52;
    int q;
    char dataTp[10];
    scanf("%d%s", &q, dataTp);
    seg.build(1, 1, m);
    for (int i = 1; i <= q; ++i) {
        char op[5];
        int l, r;
        ll x, y;
        scanf("%s", op);
        scanf("%lld%lld", &x, &y);
        x ^= lst;
        y ^= lst;
        if (op[0] == 'A') {
            ++n;
            if (n <= m)
                seg.ins(1, 1, m, n, x, y);
        } else {
            scanf("%d%d", &l, &r);
            l ^= lst;
            r ^= lst;
            lst = seg.query(1, 1, m, l, r, x, y);
            printf("%lld\n", lst);
            if (dataTp[0] == 'E')
                lst = 0;
            lst &= 0x7fffffff;
        }
    }
    return 0;
}
