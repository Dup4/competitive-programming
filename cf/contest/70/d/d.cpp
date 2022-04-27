#include <bits/stdc++.h>
using namespace std;
typedef long long db;
const db INF = 1e18;
int sgn(db x) {
    if (x == 0)
        return 0;
    return x < 0 ? -1 : 1;
}

struct Point {
    db x, y;
    Point() {}
    Point(db _x, db _y) : x(_x), y(_y) {}
    Point operator-(const Point &t) const {
        return Point(x - t.x, y - t.y);
    }
    db operator^(const Point &t) const {
        return x * t.y - y * t.x;
    }
    bool operator<(const Point &t) const {
        return sgn(x - t.x) == 0 ? sgn(y - t.y) < 0 : x < t.x;
    }
};

struct DCH {
    set<Point> st;
    db area;
    typedef set<Point>::iterator IT;
    void clear() {
        st.clear();
        area = 0;
    }
    bool in(const Point &p) const {
        if (st.empty())
            return 0;
        if (p.x < st.begin()->x)
            return 0;
        if (p.x > (--st.end())->x)
            return 0;
        IT lef = st.lower_bound(Point(p.x, -INF));
        if (p.x == lef->x)
            return p.y <= lef->y;
        IT rig = lef--;
        return sgn((p - *lef) ^ (*rig - *lef)) >= 0;
    }
    void insert(const Point &p) {
        if (in(p))
            return;
        st.insert(p);
        IT itr = st.lower_bound(p);
        if (itr != st.begin() && itr != (--st.end())) {
            IT lef = itr;
            lef--;
            IT rig = itr;
            rig++;
            area += (*lef - p) ^ (*rig - p);
        }
        if (itr == st.begin() && itr != (--st.end())) {
            IT rig = itr;
            rig++;
            area += (rig->x - p.x) * (p.y + rig->y);
        }
        if (itr != st.begin() && itr == (--st.end())) {
            IT lef = itr;
            lef--;
            area += (p.x - lef->x) * (p.y + lef->y);
        }
        if (itr != st.begin()) {
            IT now = itr;
            now--;
            while (now != st.begin()) {
                IT tmp = now;
                tmp--;
                if (sgn((*tmp - p) ^ (*now - p)) >= 0) {
                    area += (*tmp - p) ^ (*now - p);
                    st.erase(now--);
                } else
                    break;
            }
            if (now->x == p.x)
                st.erase(now);
        }
        if (itr != (--st.end())) {
            IT now = itr;
            now++;
            while (now != (--st.end())) {
                IT tmp = now;
                tmp++;
                if (sgn((*now - p) ^ (*tmp - p)) >= 0) {
                    area += (*now - p) ^ (*tmp - p);
                    st.erase(now++);
                } else
                    break;
            }
        }
    }
} up, dw;

int main() {
    up.clear();
    dw.clear();
    int q;
    scanf("%d", &q);
    while (q--) {
        int t, x, y;
        scanf("%d%d%d", &t, &x, &y);
        if (t == 1) {
            up.insert(Point(x, y));
            dw.insert(Point(x, -y));
        } else {
            bool ok = (up.in(Point(x, y)) && dw.in(Point(x, -y)));
            printf("%s\n", (ok ? "YES" : "NO"));
        }
    }
    return 0;
}
