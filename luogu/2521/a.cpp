#include<bits/stdc++.h>
using namespace std;
typedef double db;
const db eps = 1e-10;
const db PI = acos(-1.0L); 
const db INF = 1e18;
int sgn(db x) { if (fabs(x) < eps) return 0; return x < 0 ? -1 : 1; }

struct Point {
    db x, y;
    Point () {}
    Point (db _x, db _y): x(_x), y(_y) {} 
    Point operator - (const Point &t) const { return Point(x - t.x, y - t.y); }
    db operator ^ (const Point &t) const { return x * t.y - y * t.x; }
    bool operator < (const Point &t) const { return sgn(x - t.x) == 0 ? sgn(y - t.y) < 0 : x < t.x; }
	db dis(Point b) { return hypot(x - b.x, y - b.y); } 
};

struct DCH { 
    set <Point> st; 
	//维护的是整个凸壳的面积和周长
	//整个凸包的面积就是两个凸壳的面积和 
	//整个凸包的周长是两个凸壳的周长和减去两倍首尾两点的距离
    db area, perimeter;
  	typedef set <Point>::iterator IT; 
	void clear() { st.clear(); area = 0; perimeter = 0; }
    bool in(const Point &p) const {
        if (st.empty()) return 0; 
        if (p.x < st.begin()->x) return 0;
        if (p.x > (--st.end())->x) return 0;
        IT lef = st.lower_bound(Point(p.x, -INF));
        if (p.x == lef->x) return p.y <= lef->y;
        IT rig = lef--;
        return sgn((p - *lef) ^ (*rig - *lef)) >= 0;
    }
    void ins(Point p) {
        if (in(p)) return;
        st.insert(p);
        IT itr = st.lower_bound(p);
        if (itr != st.begin() && itr != (--st.end())) {
            IT lef = itr; lef--;
            IT rig = itr; rig++;
            area += (*lef - p) ^ (*rig - p);
			perimeter += p.dis(*lef);
			perimeter += p.dis(*rig);
		    Point tmpp = *lef;
			if ((int)st.size() > 3) perimeter -= tmpp.dis(*rig);	
        }
        if (itr == st.begin() && itr != (--st.end())) {
            IT rig = itr; rig++;
            area += (rig->x - p.x) * (p.y + rig->y);
    		perimeter += p.dis(*rig);   
			if ((int)st.size() > 2) {
				Point tmpp = *(--st.end());
				perimeter -= tmpp.dis(*rig);
				perimeter += tmpp.dis(p);
			}
		}
        if (itr != st.begin() && itr == (--st.end())) {
            IT lef = itr; lef--;
            area += (p.x - lef->x) * (p.y + lef->y);
        	perimeter += p.dis(*lef);
			if ((int)st.size() > 2) {
				Point tmpp = *st.begin();
				perimeter -= tmpp.dis(*lef);
				perimeter += tmpp.dis(p);
			}
		}
        if (itr != st.begin()) {
            IT now = itr; now--;
            while (now != st.begin()) {
                IT tmp = now; tmp--;
                if (sgn((*tmp - p) ^ (*now-p)) >= 0) {
                    area += (*tmp - p) ^ (*now - p);
					perimeter -= p.dis(*now);
					Point tmpp = *now; 
					perimeter -= tmpp.dis(*tmp);
					perimeter += p.dis(*tmp);
                    st.erase(now--);
                } else break;
            }
			if (now->x == p.x) {
				perimeter -= p.dis(*now);
				if ((int)st.size() > 2) {
					IT pre = now;
					if (now == st.begin()) pre = (--st.end());
					else --pre;
					Point tmpp = *now;
					perimeter -= tmpp.dis(*pre);
					perimeter += p.dis(*pre);
				} 
				st.erase(now);
			}
		} 
        if (itr != (--st.end())) {
            IT now = itr; now++;
            while (now != (--st.end())) {
                IT tmp = now; tmp++;
                if (sgn((*now - p) ^ (*tmp - p)) >= 0) {
                    area += (*now - p) ^ (*tmp - p);
					perimeter -= p.dis(*now);
					Point tmpp = *now;
					perimeter -= tmpp.dis(*tmp);
					perimeter += p.dis(*tmp);
                    st.erase(now++);
                } else break;
            }
        }
    }
}up;

const int N = 1e5 + 10;
int n, q, m, x, y, exist[N];
Point p[N];
struct E { int op, id; db ans; }e[N];

int main() {
	up.clear();
	scanf("%d%d%d", &n, &x, &y);
	up.ins(Point(0, 0));
	up.ins(Point(n, 0));
	up.ins(Point(x, y));
	scanf("%d", &m);
	for (int i = 1; i <= m; ++i) {
		exist[i] = 1;
		scanf("%lf%lf", &p[i].x, &p[i].y);
	}
	scanf("%d", &q);
	for (int i = 1; i <= q; ++i) {
		scanf("%d", &e[i].op);
		if (e[i].op == 1) {
			scanf("%d", &e[i].id);
			exist[e[i].id] = 0;
		}
	}
	for (int i = 1; i <= m; ++i) if (exist[i] == 1)
		up.ins(p[i]);
	for (int i = q; i >= 1; --i) {
		if (e[i].op == 2)
			e[i].ans = up.perimeter;
		else 
			up.ins(p[e[i].id]);
	}
	for (int i = 1; i <= q; ++i) if (e[i].op == 2)
		printf("%.2f\n", e[i].ans - n);
    return 0;
}

