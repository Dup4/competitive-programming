#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
typedef double db;
const db eps = 1e-8;
const db PI = acos(-1.0);
const int N = 1e3 + 10, INF = 0x3f3f3f3f;
int n;
db sqr(db x) {
    return x * x;
}
int sgn(db x) {
    return fabs(x) < eps ? 0 : x < 0 ? -1 : 1;
}

struct Point {
    db x, y;
    Point(db x = 0, db y = 0) : x(x), y(y) {}
    void scan() {
        db _x, _y;
        scanf("%lf%lf", &_x, &_y);
        x = _x, y = _y;
    }
    void print() {
        printf("%.11f %.11f\n", x, y);
    }
    bool operator==(const Point &b) const {
        return sgn(x - b.x) == 0 && sgn(y - b.y) == 0;
    }
    bool operator<(const Point &b) const {
        return sgn(x - b.x) == 0 ? sgn(y - b.y) < 0 : x < b.x;
    }
    Point operator+(const Point &b) const {
        return Point(x + b.x, y + b.y);
    }
    Point operator-(const Point &b) const {
        return Point(x - b.x, y - b.y);
    }
    Point operator*(const db &b) const {
        return Point(x * b, y * b);
    }
    Point operator/(const db &b) const {
        return Point(x / b, y / b);
    }
    db operator^(const Point &b) const {
        return x * b.y - y * b.x;
    }
    db operator*(const Point &b) const {
        return x * b.x + y * b.y;
    }
    db len() {
        return hypot(x, y);
    }
    db dis(Point b) {
        return hypot(x - b.x, y - b.y);
    }
};

struct Circle {
    Point p;
    db r;
    Circle() {}
    Circle(Point p, db r) : p(p), r(r) {}
    Circle(db x, db y, db r) : p(Point(x, y)), r(r) {}
    void scan() {
        p.scan();
        scanf("%lf", &r);
    }
    void print() {
        printf("%.10f %.10f %.10f\n", p.x, p.y, r);
    }
    bool operator==(const Circle &b) const {
        return (p == b.p) && sgn(r - b.r) == 0;
    }
    bool operator<(const Circle &b) const {
        return ((p < b.p) || ((p == b.p) && sgn(r - b.r) < 0));
    }
    db area() {
        return PI * r * r;
    }
    db circumference() {
        return PI * r * 2;
    }
    //两圆的关系
    // 5 相离
    // 4 外切
    // 3 相交
    // 2 内切
    // 1 内含
    // UVA12304
    int relationCircle(Circle b) {
        db dis = p.dis(b.p);
        if (sgn(dis - r - b.r) > 0)
            return 5;
        if (sgn(dis - r - b.r) == 0)
            return 4;
        db l = fabs(r - b.r);
        if (sgn(dis - r - b.r) && sgn(dis - l) > 0)
            return 3;
        if (sgn(dis - l) == 0)
            return 2;
        if (sgn(dis - l) < 0)
            return 1;
        //不可达分支
        return 0;
    }
    //本圆是否被圆b包含
    bool InnerCircle(Circle b) {
        if (relationCircle(b) != 1)
            return 0;
        return sgn(r - b.r) <= 0 ? 1 : 0;
    }
};

struct CircleUnion {
    vector<Circle> cir;
    // ans[i] 表示被覆盖了i次的面积
    vector<db> ans, pre;
    int sze() {
        return cir.size();
    }
    CircleUnion(int n = 0) {
        cir.clear();
        cir.resize(n);
    }
    void scan(int n = -1) {
        if (n == -1)
            scanf("%d", &n);
        (*this) = CircleUnion(n);
        for (int i = 0; i < n; ++i) cir[i].scan();
    }
    void add(Circle c) {
        cir.push_back(c);
    }
    Circle &operator[](int x) {
        return cir[x];
    }
    //返回 半径为r的圆 弧度为th的弓形的面积
    db areaArc(db th, db r) {
        return 0.5 * r * r * (th - sin(th));
    }
    //去掉相同圆及内含圆
    //求圆并的时候需要调用 然后答案就是 \sum ans[i]
    void init_Unique() {
        vector<bool> mark(sze() + 5, 0);
        for (int i = 0; i < sze(); ++i) {
            for (int j = 0; j < sze(); ++j) {
                if (i != j && !mark[j]) {
                    if (cir[i] == cir[j] || cir[i].InnerCircle(cir[j])) {
                        mark[i] = 1;
                        break;
                    }
                }
            }
        }
        int cnt = 0;
        for (int i = 0; i < sze(); ++i) {
            if (!mark[i]) {
                cir[cnt++] = cir[i];
            }
        }
        cir.resize(cnt);
    }
    void gao() {
        ans.clear();
        ans.resize(sze() + 5, 0);
        pre.clear();
        pre.resize(sze() + 5, 0);
        vector<pair<db, int> > v;
        for (int i = 0; i < sze(); ++i) {
            v.clear();
            v.push_back(make_pair(-PI, 1));
            v.push_back(make_pair(PI, -1));
            for (int j = 0; j < sze(); ++j) {
                if (i != j) {
                    Point q = (cir[j].p - cir[i].p);
                    db ab = q.len(), ac = cir[i].r, bc = cir[j].r;
                    if (sgn(ab + ac - bc) <= 0) {
                        v.push_back(make_pair(-PI, 1));
                        v.push_back(make_pair(PI, -1));
                        continue;
                    }
                    if (sgn(ab - ac + bc) <= 0)
                        continue;
                    if (sgn(ab - ac - bc) > 0)
                        continue;
                    db th = atan2(q.y, q.x), fai = acos((ac * ac + ab * ab - bc * bc) / (2.0 * ac * ab));
                    db a0 = th - fai;
                    if (sgn(a0 + PI) < 0)
                        a0 += PI * 2;
                    db a1 = th + fai;
                    if (sgn(a1 - PI) > 0)
                        a1 -= PI * 2;
                    if (sgn(a0 - a1) > 0) {
                        v.push_back(make_pair(a0, 1));
                        v.push_back(make_pair(PI, -1));
                        v.push_back(make_pair(-PI, 1));
                        v.push_back(make_pair(a1, -1));
                    } else {
                        v.push_back(make_pair(a0, 1));
                        v.push_back(make_pair(a1, -1));
                    }
                }
            }
            sort(v.begin(), v.end());
            int cur = 0;
            for (int j = 0; j < (int)v.size(); ++j) {
                if (cur > 0 && sgn(v[j].fi - pre[cur])) {
                    ans[cur] += areaArc(v[j].fi - pre[cur], cir[i].r);
                    ans[cur] +=
                            0.5 *
                            (Point(cir[i].p.x + cir[i].r * cos(pre[cur]), cir[i].p.y + cir[i].r * sin(pre[cur])) ^
                                    Point(cir[i].p.x + cir[i].r * cos(v[j].fi), cir[i].p.y + cir[i].r * sin(v[j].fi)));
                }
                cur += v[j].se;
                if (cur > 0)
                    pre[cur] = v[j].fi;
            }
        }
        for (int i = 1; i < sze(); ++i) ans[i] -= ans[i + 1];
    }
};

int main() {
    while (scanf("%d", &n) != EOF) {
        CircleUnion cu;
        cu.scan(n);
        cu.gao();
        for (int i = 1; i <= n; ++i) {
            printf("[%d] = %.3f\n", i, cu.ans[i]);
        }
        return 0;
    }
}
