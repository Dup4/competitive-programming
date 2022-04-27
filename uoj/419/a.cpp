#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef double db;
const int N = 2e3 + 10;
const db PI = acos(-1.0);
inline db sqr(db x) {
    return 1. * x * x;
}
int n;

struct Point {
    db x, y;
    Point() {}
    Point(db _x, db _y) : x(_x), y(_y) {}
    void scan() {
        scanf("%lf%lf", &x, &y);
    }
    Point operator+(const Point &b) const {
        return Point(x + b.x, y + b.y);
    }
    Point operator-(const Point &b) const {
        return Point(x - b.x, y - b.y);
    }
    db len() {
        return hypot(x, y);
    }
    db ang() {
        return atan2(y, x);
    }
};

struct Circle {
    Point p;
    db r;
    void scan() {
        p.scan();
        scanf("%lf", &r);
    }
    db oint(db t1, db t2) {
        return r * (r * (t2 - t1) + p.x * (sin(t2) - sin(t1)) - p.y * (cos(t2) - cos(t1)));
    }
    bool in(const Circle &b) const {
        return (p - b.p).len() + b.r <= r;
    }
    bool out(const Circle &b) const {
        return r + b.r <= (p - b.p).len();
    }
} c[N];

namespace CircleUnion {
struct node {
    db l, r;
    node(db l = 0, db r = 0) : l(l), r(r) {}
    bool operator<(const node &b) const {
        return r < b.r;
    }
};
set<node> s[N];
db res;
bool vis[N];
typedef set<node>::iterator IT;
inline void fix(db &ang) {
    if (ang < -PI)
        ang += PI * 2;
    if (ang > PI)
        ang -= PI * 2;
}
void remove(int id, db l, db r) {
    if (l > r) {
        remove(id, -PI, r);
        remove(id, l, +PI);
        return;
    }
    for (IT it = s[id].lower_bound(node(0, l)), tmp; it != s[id].end() && it->l < r; it = tmp) {
        db nl = it->l, nr = it->r;
        tmp = it, ++tmp;
        s[id].erase(it), res -= c[id].oint(nl, nr);
        if (nl < l)
            s[id].insert(node(nl, l)), res += c[id].oint(nl, l);
        if (nr > r)
            s[id].insert(node(r, nr)), res += c[id].oint(r, nr);
    }
}
void del(int i, int j) {
    db dis = (c[i].p - c[j].p).len(), ang, cur, l, r;
    cur = (c[j].p - c[i].p).ang();
    //求圆心到交点的线和两圆心连线之间的角度
    ang = acos((sqr(dis) + sqr(c[i].r) - sqr(c[j].r)) / (c[i].r * dis * 2));
    fix(l = cur - ang);
    fix(r = cur + ang);
    remove(i, l, r);
}
void gao() {
    res = 0;
    for (int i = 1; i <= n; ++i) {
        vis[i] = 1;
        for (int j = 1; j < i; ++j)
            if (vis[j]) {
                if (c[j].r >= c[i].r && c[j].in(c[i])) {
                    vis[i] = 0;
                    break;
                }
                if (c[i].r > c[j].r && c[i].in(c[j])) {
                    vis[j] = 0;
                    remove(j, -PI, +PI);
                }
            }
        if (!vis[i]) {
            printf("%.10f\n", res * 0.5);
            continue;
        }
        res += c[i].r * c[i].r * PI * 2;
        s[i].clear();
        s[i].insert(node(-PI, PI));
        for (int j = 1; j < i; ++j)
            if (vis[j] && !c[i].out(c[j]))
                del(i, j), del(j, i);
        printf("%.10f\n", res * 0.5);
    }
}
}  // namespace CircleUnion

int main() {
    scanf("%*d%d", &n);
    for (int i = 1; i <= n; ++i) c[i].scan();
    CircleUnion::gao();
    return 0;
}
