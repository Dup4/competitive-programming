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
        Point() {}
        Point(db _x, db _y) : x(_x), y(_y) {}
        bool operator==(const Point &t) const {
            return sgn(x - t.x) == 0 && sgn(y - t.y) == 0;
        }
        Point operator-(const Point &t) const {
            return Point(x - t.x, y - t.y);
        }
        db operator^(const Point &t) const {
            return x * t.y - y * t.x;
        }
        db dis(Point b) {
            return hypot(x - b.x, y - b.y);
        }
    };
    struct node {
        Point p;
        mutable Point next_p;
        int opt;
        // 0 set中排序使用
        // 1 查询使用
        node(Point p = Point(0, 0), Point next_p = Point(0, 0), int opt = 0) : p(p), next_p(next_p), opt(opt) {}
        bool operator<(const node &other) const {
            if (opt) {
                return sgn(p.x * (other.next_p.x - other.p.x) + p.y * (other.next_p.y - other.p.y)) <= 0;
            } else {
                return sgn(p.x - other.p.x) == 0 ? sgn(p.y - other.p.y) < 0 : p.x < other.p.x;
            }
        }
    };
    set<node> st;
    db area, perimeter;
    typedef set<node>::iterator IT;
    void init() {
        st.clear();
        area = 0;
        perimeter = 0;
    }
    int size() {
        return st.size();
    }
    //判断点是否在凸壳内
    //如果要判断点是否在凸包内，维护上凸壳和下凸壳，点要满足同时在两个凸壳内
    // CF 70D
    bool inside(const Point &p) const {
        if (st.empty())
            return 0;
        if (p.x < st.begin()->p.x)
            return 0;
        if (p.x > (--st.end())->p.x)
            return 0;
        IT lef = st.lower_bound(Point(p.x, -INF));
        if (p.x == lef->p.x)
            return p.y <= lef->p.y;
        IT rig = lef--;
        return sgn((p - lef->p) ^ (rig->p - lef->p)) >= 0;
    }
    void insert(Point p) {
        if (inside(p))
            return;
        st.insert(node(p, p));
        IT itr = st.lower_bound(p);
        if (itr != st.begin() && itr != (--st.end())) {
            IT lef = itr;
            lef--;
            IT rig = itr;
            rig++;
            lef->next_p = itr->p;
            itr->next_p = rig->p;
            area += (lef->p - p) ^ (rig->p - p);
            perimeter += p.dis(lef->p);
            perimeter += p.dis(rig->p);
            Point tmpp = lef->p;
            perimeter -= tmpp.dis(rig->p);
        }
        if (itr == st.begin() && itr != (--st.end())) {
            IT rig = itr;
            rig++;
            itr->next_p = rig->p;
            area += (rig->p.x - p.x) * (p.y + rig->p.y);
            perimeter += p.dis(rig->p);
        }
        if (itr != st.begin() && itr == (--st.end())) {
            IT lef = itr;
            lef--;
            lef->next_p = itr->p;
            area += (p.x - lef->p.x) * (p.y + lef->p.y);
            perimeter += p.dis(lef->p);
        }
        if (itr != st.begin()) {
            IT now = itr;
            now--;
            while (now != st.begin()) {
                IT tmp = now;
                tmp--;
                if (sgn((tmp->p - p) ^ (now->p - p)) >= 0) {
                    tmp->next_p = itr->p;
                    area += (tmp->p - p) ^ (now->p - p);
                    perimeter -= p.dis(now->p);
                    Point tmpp = now->p;
                    perimeter -= tmpp.dis(tmp->p);
                    perimeter += p.dis(tmp->p);
                    st.erase(now--);
                } else
                    break;
            }
            if (now->p.x == p.x) {
                if (now != st.begin()) {
                    IT tmp = now;
                    tmp--;
                    tmp->next_p = itr->p;
                }
                perimeter -= p.dis(now->p);
                if ((int)st.size() > 2 && now != st.begin()) {
                    IT pre = now;
                    if (now == st.begin())
                        pre = (--st.end());
                    else
                        --pre;
                    Point tmpp = now->p;
                    perimeter -= tmpp.dis(pre->p);
                    perimeter += p.dis(pre->p);
                }
                st.erase(now);
            }
        }
        if (itr != (--st.end())) {
            IT now = itr;
            now++;
            while (now != (--st.end())) {
                IT tmp = now;
                tmp++;
                if (sgn((now->p - p) ^ (tmp->p - p)) >= 0) {
                    itr->next_p = tmp->p;
                    area += (now->p - p) ^ (tmp->p - p);
                    perimeter -= p.dis(now->p);
                    Point tmpp = now->p;
                    perimeter -= tmpp.dis(tmp->p);
                    perimeter += p.dis(tmp->p);
                    st.erase(now++);
                } else
                    break;
            }
        }
    }
    void insert(db x, db y = 0) {
        insert(Point(x, y));
    }
    //查询max(ax + by)
    db query(db a, db b) {
        if (size() == 0)
            return -INF;
        IT it = st.upper_bound(node(Point(a, b), Point(0, 0), 1));
        return it->p.x * a + b * it->p.y;
    }
    //传入下凸壳，用于计算整个凸包的周长
    // LightOJ 1239
    db calcPerimeter(DCH &down) {
        Point up_begin = st.begin()->p;
        Point down_begin = down.st.begin()->p;
        Point up_end = (--st.end())->p;
        Point down_end = (--down.st.end())->p;
        down_begin.y *= -1;
        down_end.y *= -1;
        db res = perimeter + down.perimeter;
        if (!(up_begin == down_begin))
            res += up_begin.dis(down_begin);
        if (!(up_end == down_end))
            res += up_end.dis(down_end);
        return res;
    }
    //传入下凸壳, 用于计算整个凸包的面积
    // POJ 3348
    db calcArea(DCH &down) {
        db res = area + down.area;
        return res / 2;
    }
};

int main() {
    int n;
    scanf("%d", &n);
    DCH up, down;
    up.init();
    down.init();
    long long x, y;
    for (int i = 1; i <= n; ++i) {
        scanf("%lld%lld", &x, &y);
        up.insert(x, y);
        down.insert(x, -y);
    }
    printf("%lld\n", up.calcArea(down) / 50);
    return 0;
}
