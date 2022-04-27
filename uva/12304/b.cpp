#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
using namespace std;
const double eps = 1e-8;
const double inf = 1e20;
const double pi = acos(-1.0);
const int maxn = 1010;
int sgn(double x) {
    if (fabs(x) < eps)
        return 0;
    if (x < 0)
        return -1;
    else
        return 1;
}
struct Point {
    double x, y;
    Point(){};
    Point(double _x, double _y) {
        x = _x;
        y = _y;
    }
    void input() {
        scanf("%lf%lf", &x, &y);
    }
    bool operator<(Point b) const {
        return sgn(x - b.x) == 0 ? sgn(y - b.y) < 0 : x < b.x;
    }
    bool operator==(Point b) const {
        return sgn(x - b.x) == 0 && sgn(y - b.y) == 0;
    }
    Point operator+(const Point &b) const {
        return Point(x + b.x, y + b.y);
    }
    Point operator-(const Point &b) const {
        return Point(x - b.x, y - b.y);
    }
    Point operator/(const double &b) const {
        return Point(x / b, y / b);
    }
    Point operator*(const double &b) const {
        return Point(x * b, y * b);
    }
    double operator^(const Point &b) const {
        return x * b.y - y * b.x;
    }
    double operator*(const Point &b) const {
        return x * b.x + y * b.y;
    }
    double len() {
        return hypot(x, y);
    }
    double len2() {
        return x * x + y * y;
    }
    Point trunc(double r) {
        double l = len();
        if (!sgn(l))
            return *this;
        r /= l;
        return Point(x * r, y * r);
    }
    Point rotleft() {
        return Point(-y, x);
    }
    Point rotright() {
        return Point(y, -x);
    }
    double distance(Point p) {
        return hypot(x - p.x, y - p.y);
    }
};
struct Line {
    Point s, e;
    Line(){};
    Line(Point _s, Point _e) {
        s = _s;
        e = _e;
    }
    void input() {
        s.input();
        e.input();
    }
    double legth() {
        return s.distance(e);
    }
    double angle() {
        double k = atan2(e.y - s.y, e.x - s.x);
        if (sgn(k) < 0)
            k += pi;
        if (sgn(k - pi) == 0)
            k -= pi;
        return k;
    }
    Point cross_point(Line v) {
        double a1 = (v.e - v.s) ^ (s - v.s);
        double a2 = (v.e - v.s) ^ (e - v.s);
        return Point((s.x * a2 - e.x * a1) / (a2 - a1), (s.y * a2 - e.y * a1) / (a2 - a1));
    }
    double dis_point_to_line(Point p) {
        return fabs((p - s) ^ (e - s)) / legth();
    }
    double dis_point_to_seg(Point p) {
        if (sgn((p - s) * (e - s)) < 0 || sgn((p - e) * (s - e)) < 0)
            return min(p.distance(s), p.distance(e));
        return dis_point_to_line(p);
    }
    //返回点p在直线上的投影
    Point line_prog(Point p) {
        return s + (((e - s) * ((e - s) * (p - s))) / ((e - s).len2()));
    }
    bool parallel(Line v) {
        return sgn((e - s) ^ (v.e - v.s)) == 0;
    }
};
struct circle {
    Point p;
    double r;
    circle(){};
    circle(Point _p, double _r) {
        p = _p;
        r = _r;
    }
    circle(double x, double y, double _r) {
        p = Point(x, y);
        r = _r;
    }
    //三角形的外接圆
    circle(Point a, Point b, Point c) {
        Line u = Line((a + b) / 2, ((a + b) / 2) + ((b - a).rotleft()));
        Line v = Line((b + c) / 2, ((b + c) / 2) + ((c - b).rotleft()));
        p = u.cross_point(v);
        r = p.distance(a);
    }
    //三角形内切圆
    circle(Point a, Point b, Point c, bool t) {
        Line u, v;
        double m = atan2(b.y - a.y, b.x - a.x), n = atan2(c.y - a.y, c.x - a.x);
        u.s = a;
        u.e = u.s + Point(cos((n + m) / 2), sin((n + m) / 2));
        v.s = b;
        m = atan2(a.y - b.y, a.x - b.x), n = atan2(c.y - b.y, c.x - b.x);
        v.e = v.s + Point(cos((n + m) / 2), sin((n + m) / 2));
        p = u.cross_point(v);
        r = Line(a, b).dis_point_to_seg(p);
    }
    void input() {
        p.input();
        scanf("%lf", &r);
    }
    int relation_point(Point b) {
        double dist = b.distance(p);
        if (sgn(dist - r) < 0)
            return 2;
        else if (sgn(dist - r) == 0)
            return 1;
        return 0;
    }
    //求直线和圆的交点
    int relation_line(Line v) {
        double dist = v.dis_point_to_line(p);
        if (sgn(dist - r) < 0)
            return 2;
        else if (sgn(dist - r) == 0)
            return 1;
        return 0;
    }
    int relation_circle(circle v) {
        double d = p.distance(v.p);
        if (sgn(d - r - v.r) > 0)
            return 5;
        if (sgn(d - r - v.r) == 0)
            return 4;
        double l = fabs(r - v.r);
        if (sgn(d - r - v.r) < 0 && sgn(d - l) > 0)
            return 3;
        if (sgn(d - l) == 0)
            return 2;
        if (sgn(d - l) < 0)
            return 1;
    }
    int point_cross_line(Line v, Point &p1, Point &p2) {
        if (!(*this).relation_line(v))
            return 0;
        Point a = v.line_prog(p);
        double d = v.dis_point_to_line(p);
        d = sqrt(r * r - d * d);
        if (sgn(d) == 0) {
            p1 = a;
            p2 = a;
            return 1;
        }
        p1 = a + (v.e - v.s).trunc(d);
        p2 = a - (v.e - v.s).trunc(d);
        return 2;
    }
    int point_cross_circle(circle v, Point &p1, Point &p2) {
        int rel = relation_circle(v);
        if (rel == 1 || rel == 5)
            return 0;
        double d = p.distance(v.p);
        double l = (d * d + r * r - v.r * v.r) / (2 * d);
        double h = sqrt(r * r - l * l);
        Point temp = p + (v.p - p).trunc(l);
        p1 = temp + ((v.p - p).rotleft().trunc(h));
        p2 = temp + ((v.p - p).rotright().trunc(h));
        if (rel == 2 || rel == 4) {
            return 1;
        }
        return 2;
    }
    int tangent_line(Point q, Line &u, Line &v) {
        int x = relation_point(q);
        if (x == 2)
            return 0;
        if (x == 1) {
            u = Line(q, q + (q - p).rotleft());
            v = u;
            return 1;
        }
        double d = p.distance(q);
        double l = r * r / d;
        double h = sqrt(r * r - l * l);
        u = Line(q, p + ((q - p).trunc(l) + (q - p).rotleft().trunc(h)));
        v = Line(q, p + ((q - p).trunc(l) + (q - p).rotright().trunc(h)));
        return 2;
    }
    //得过与直线u相切，过点q，半径为r1的圆
    int get_circle(Line u, Point q, double r1, circle &c1, circle &c2) {
        double dis = u.dis_point_to_line(q);
        if (sgn(dis - r1 * 2) > 0)
            return 0;
        if (sgn(dis) == 0) {
            c1.p = q + ((u.e - u.s).rotleft().trunc(r1));
            c2.p = q + ((u.e - u.s).rotright().trunc(r1));
            c1.r = c2.r = r1;
            return 2;
        }
        Line u1 = Line((u.s + (u.e - u.s).rotleft().trunc(r1)), (u.e + (u.e - u.s).rotleft().trunc(r1)));
        Line u2 = Line((u.s + (u.e - u.s).rotright().trunc(r1)), (u.e + (u.e - u.s).rotright().trunc(r1)));
        circle cc = circle(q, r1);
        Point p1, p2;
        if (!cc.point_cross_line(u1, p1, p2))
            cc.point_cross_line(u2, p1, p2);
        c1 = circle(p1, r1);
        if (p1 == p2) {
            c2 = c1;
            return 1;
        }
        c2 = circle(p2, r1);
        return 2;
    }
    //同时与直线u，v相切，半径为r1的圆;
    int get_circle(Line u, Line v, double r1, circle &c1, circle &c2, circle &c3, circle &c4) {
        if (u.parallel(v))
            return 0;
        Line u1 = Line(u.s + (u.e - u.s).rotleft().trunc(r1), u.e + (u.e - u.s).rotleft().trunc(r1));
        Line u2 = Line(u.s + (u.e - u.s).rotright().trunc(r1), u.e + (u.e - u.s).rotright().trunc(r1));
        Line v1 = Line(v.s + (v.e - v.s).rotleft().trunc(r1), v.e + (v.e - v.s).rotleft().trunc(r1));
        Line v2 = Line(v.s + (v.e - v.s).rotright().trunc(r1), v.e + (v.e - v.s).rotright().trunc(r1));
        c1.r = c2.r = c3.r = c4.r = r1;
        c1.p = u1.cross_point(v1);
        c2.p = u1.cross_point(v2);
        c3.p = u2.cross_point(v1);
        c4.p = u2.cross_point(v2);
        return 4;
    }
    //同时与不相交的两个圆cx,cy相切  ，半径为r1的圆
    int get_circle(circle cx, circle cy, double r1, circle &c1, circle &c2) {
        circle x(cx.p, r1 + cx.r), y(cy.p, r1 + cy.r);
        int t = x.point_cross_circle(y, c1.p, c2.p);
        if (!t)
            return 0;
        c1.r = c2.r = r1;
        return t;
    }
};
int main() {
    string s;
    while (cin >> s) {
        if (s == "CircumscribedCircle") {
            Point a1, a2, a3;
            a1.input();
            a2.input();
            a3.input();
            circle ans(a1, a2, a3);
            printf("(%.6lf,%.6lf,%.6lf)\n", ans.p.x, ans.p.y, ans.r);
        }
        if (s == "InscribedCircle") {
            Point a1, a2, a3;
            a1.input();
            a2.input();
            a3.input();
            circle ans(a1, a2, a3, true);
            printf("(%.6lf,%.6lf,%.6lf)\n", ans.p.x, ans.p.y, ans.r);
        }
        if (s == "TangentLineThroughPoint") {
            circle c;
            c.input();
            Point pp;
            pp.input();
            Line uu, vv;
            int ans = c.tangent_line(pp, uu, vv);
            if (ans == 0)
                printf("[]\n");
            if (ans == 1)
                printf("[%.6lf]\n", uu.angle() / pi * 180.0);
            if (ans == 2) {
                double res[5];
                res[0] = uu.angle();
                res[1] = vv.angle();
                sort(res, res + 2);
                printf("[%.6lf,%.6lf]\n", res[0] / pi * 180.0, res[1] / pi * 180.0);
            }
        }
        if (s == "CircleThroughAPointAndTangentToALineWithRadius") {
            Point pp;
            pp.input();
            Line uu;
            uu.input();
            double rr;
            scanf("%lf", &rr);
            circle c, c1, c2;
            int ans = c.get_circle(uu, pp, rr, c1, c2);
            if (ans == 0)
                printf("[]\n");
            if (ans == 1)
                printf("[(%.6lf,%.6lf)]\n", c1.p.x, c1.p.y);
            if (ans == 2) {
                Point yx[5];
                yx[0] = c1.p;
                yx[1] = c2.p;
                sort(yx, yx + 2);
                printf("[(%.6lf,%.6lf),(%.6lf,%.6lf)]\n", yx[0].x, yx[0].y, yx[1].x, yx[1].y);
            }
        }
        if (s == "CircleTangentToTwoLinesWithRadius") {
            Line u, v;
            double r1;
            circle c, c1, c2, c3, c4;
            u.input();
            v.input();
            scanf("%lf", &r1);
            c.get_circle(u, v, r1, c1, c2, c3, c4);
            Point yx[5];
            yx[0] = c1.p;
            yx[1] = c2.p;
            yx[2] = c3.p;
            yx[3] = c4.p;
            sort(yx, yx + 4);
            printf("[(%.6lf,%.6lf),(%.6lf,%.6lf),(%.6lf,%.6lf),(%.6lf,%.6lf)]\n", yx[0].x, yx[0].y, yx[1].x, yx[1].y,
                    yx[2].x, yx[2].y, yx[3].x, yx[3].y);
        }
        if (s == "CircleTangentToTwoDisjointCirclesWithRadius") {
            circle c, cx, cy, c1, c2;
            cx.input();
            cy.input();
            double r1;
            scanf("%lf", &r1);
            int ans = c.get_circle(cx, cy, r1, c1, c2);
            if (ans == 0)
                printf("[]\n");
            if (ans == 1)
                printf("[(%.6lf,%.6lf)]\n", c1.p.x, c1.p.y);
            if (ans == 2) {
                Point yx[5];
                yx[0] = c1.p;
                yx[1] = c2.p;
                sort(yx, yx + 2);
                printf("[(%.6lf,%.6lf),(%.6lf,%.6lf)]\n", yx[0].x, yx[0].y, yx[1].x, yx[1].y);
            }
        }
    }
}
