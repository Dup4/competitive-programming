#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <set>
#include <vector>
using namespace std;
typedef long long db;
const db eps = 1e-8;
const db PI = acos(-1.0);
const db INF = 1e18;
int sgn(db x) {
    if (x == 0)
        return 0;
    return x < 0 ? -1 : 1;
}
// int sgn(db x) { if (fabs(x) < eps) return 0; return x < 0 ? -1 : 1; }

struct DCH {
    struct Point {
        db x, y;
        double alpha;
        Point() {}
        Point(db _x, db _y, double _alpha = 0) : x(_x), y(_y), alpha(_alpha) {}
        Point operator-(const Point &t) const {
            return Point(x - t.x, y - t.y);
        }
        bool operator==(const Point &t) const {
            return sgn(x - t.x) == 0 && sgn(y - t.y) == 0;
        }
        bool operator<(const Point &t) const {
            return alpha < t.alpha;
        }
        db operator^(const Point &t) const {
            return x * t.y - y * t.x;
        }
        db dis(Point t) {
            return hypot(x - t.x, y - t.y);
        }
    };
    //点逆时针排序
    set<Point> st;
    db area;
    double perimeter;
    double Ox, Oy;
    typedef set<Point>::iterator IT;
    void init() {
        st.clear();
    }
    int size() {
        return st.size();
    }
    double calcAlpha(Point p) {
        return atan2(1.0 * p.y - Oy, 1.0 * p.x - Ox);
    }
    Point getPrev(Point p) {
        IT it = st.lower_bound(p);
        if (sgn(it->x - p.x) == 0 && sgn(it->y - p.y) == 0)
            return p;
        if (it != st.begin())
            return *--it;
        return *--st.end();
    }
    Point getNext(Point p) {
        IT it = st.upper_bound(p);
        if (it == st.end())
            return *st.begin();
        return *it;
    }
    //判断点是否在凸包内
    // Cf70D
    bool isInside(Point p) {
        if (size() < 3)
            return 0;
        p.alpha = calcAlpha(p);
        Point pre = getPrev(p);
        Point nx = getNext(p);
        return sgn((nx - pre) ^ (p - pre)) >= 0;
    }
    //计算周长
    // LuoguP2521
    db calcPerimeter() {
        if (size() < 2)
            return 0;
        if (size() == 2) {
            Point q[2] = {*st.begin(), *++st.begin()};
            return q[0].dis(q[1]) * 2;
        }
        return perimeter;
    }
    //计算面积
    // POJ3348
    db calcArea() {
        if (size() < 3)
            return 0;
        return area / 2;
    }
    //无法处理三点共线的情况, 需要满足前三个点一定能构成凸包
    void insert(Point p) {
        if (size() < 2) {
            p.alpha = size();
            st.insert(p);
            return;
        }
        if (size() == 2) {
            Point q[3] = {*st.begin(), *++st.begin(), p};
            double rands[] = {0.4352341254, 0.8242147544, 0.3614575554};
            double sum = 0;
            Ox = 0;
            Oy = 0;
            for (int i = 0; i < 3; ++i) {
                sum += rands[i];
                Ox += rands[i] * q[i].x;
                Oy += rands[i] * q[i].y;
            }
            Ox /= sum;
            Oy /= sum;
            st.clear();
            for (int i = 0; i < 3; ++i) {
                q[i].alpha = calcAlpha(q[i]);
                st.insert(q[i]);
            }
            IT it = st.begin();
            for (int i = 0; i < 3; ++i) {
                q[i] = *it;
                ++it;
            }
            perimeter = 0;
            area = 0;
            perimeter += q[0].dis(q[1]) + q[1].dis(q[2]) + q[2].dis(q[0]);
            area += (q[0] ^ q[1]) + (q[1] ^ q[2]) + (q[2] ^ q[0]);
            return;
        }
        p.alpha = calcAlpha(p);
        if (isInside(p))
            return;
        while (true) {
            Point next1 = getNext(p);
            st.erase(next1);
            Point next2 = getNext(p);
            if (sgn((next2 - p) ^ (next1 - p)) < 0) {
                st.insert(next1);
                break;
            }
            Point pre = getPrev(next1);
            perimeter -= pre.dis(next1);
            perimeter -= next1.dis(next2);
            perimeter += pre.dis(next2);
            area -= pre ^ next1;
            area -= next1 ^ next2;
            area += pre ^ next2;
        }
        while (true) {
            Point prev1 = getPrev(p);
            st.erase(prev1);
            Point prev2 = getPrev(p);
            if (sgn((p - prev2) ^ (prev1 - prev2)) < 0) {
                st.insert(prev1);
                break;
            }
            Point nx = getNext(prev1);
            perimeter -= prev1.dis(nx);
            perimeter -= prev2.dis(prev1);
            perimeter += prev2.dis(nx);
            area -= prev1 ^ nx;
            area -= prev2 ^ prev1;
            area += prev2 ^ nx;
        }
        Point pre = getPrev(p);
        Point nx = getNext(p);
        st.insert(p);
        perimeter -= pre.dis(nx);
        perimeter += pre.dis(p);
        perimeter += p.dis(nx);
        area -= pre ^ nx;
        area += pre ^ p;
        area += p ^ nx;
    }
    void insert(db x, db y) {
        insert(Point(x, y));
    }
};

int main() {
    int n;
    scanf("%d", &n);
    DCH dch;
    dch.init();
    long long x, y;
    for (int i = 1; i <= n; ++i) {
        scanf("%lld%lld", &x, &y);
        dch.insert(x, y);
    }
    printf("%lld\n", dch.calcArea() / 50);
    return 0;
}
