#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef double db;
typedef pair<db, db> pDD;
const db eps = 1e-10;
const db PI = acos(-1.0L); 
const db INF = 1e18;
int sgn(db x) { if (fabs(x) < eps) return 0; return x < 0 ? -1 : 1; }

struct DCH { 
	struct Point {
	    db x, y;
	    Point () {}
	    Point (db _x, db _y): x(_x), y(_y) {} 
	    Point operator - (const Point &t) const { return Point(x - t.x, y - t.y); }
	    db operator ^ (const Point &t) const { return x * t.y - y * t.x; }
		db dis(Point b) { return hypot(x - b.x, y - b.y); } 
	};
	struct node {
		Point p;
		mutable Point next_p;
		int opt;
		//0 set中排序使用
		//1 查询使用
		node(Point p = Point(0, 0), Point next_p = Point(0, 0), int opt = 0) : p(p), next_p(next_p), opt(opt) {}
		bool operator < (const node &other) const {
			if (opt) {
            	return sgn(p.x * (other.next_p.x - other.p.x) + p.y * (other.next_p.y - other.p.y)) <= 0;
			} else {
				return sgn(p.x - other.p.x) == 0 ? sgn(p.y - other.p.y) < 0 : p.x < other.p.x;
			}
		}
	}; 
	set <node> st; 
	//维护的是整个凸壳的面积和周长
	//整个凸包的面积就是两个凸壳的面积和 
	//整个凸包的周长是两个凸壳的周长和
    db area, perimeter;
  	typedef set <node>::iterator IT; 
	void init() { st.clear(); area = 0; perimeter = 0; }
	int size() { return st.size(); }
    bool inside(const Point &p) const {
        if (st.empty()) return 0; 
        if (p.x < st.begin()->p.x) return 0;
        if (p.x > (--st.end())->p.x) return 0;
        IT lef = st.lower_bound(Point(p.x, -INF)); 
        if (p.x == lef->p.x) return p.y <= lef->p.y;
        IT rig = lef--;
        return sgn((p - lef->p) ^ (rig->p - lef->p)) >= 0;
    }
    void insert(Point p) {
        if (inside(p)) return;
        st.insert(node(p, p));  
        IT itr = st.lower_bound(p);
        if (itr != st.begin() && itr != (--st.end())) { 
            IT lef = itr; lef--;
            IT rig = itr; rig++;
           	lef->next_p = itr->p;
		   	itr->next_p = rig->p; 
			area += (lef->p - p) ^ (rig->p - p);
			perimeter += p.dis(lef->p);
			perimeter += p.dis(rig->p);
		    Point tmpp = lef->p;
		//	if ((int)st.size() > 3) 
			perimeter -= tmpp.dis(rig->p);
        }
        if (itr == st.begin() && itr != (--st.end())) {
            IT rig = itr; rig++;
			itr->next_p = rig->p;
            area += (rig->p.x - p.x) * (p.y + rig->p.y);
    		perimeter += p.dis(rig->p);   
		//	if ((int)st.size() > 2) {
		//		Point tmpp = (--st.end())->p;
		//		perimeter -= tmpp.dis(rig->p);
		//		perimeter += tmpp.dis(p);
		//	}
		}
        if (itr != st.begin() && itr == (--st.end())) {
            IT lef = itr; lef--;
			lef->next_p = itr->p; 
            area += (p.x - lef->p.x) * (p.y + lef->p.y);
        	perimeter += p.dis(lef->p);
		//	if ((int)st.size() > 2) {
		//		Point tmpp = st.begin()->p;
		//		perimeter -= tmpp.dis(lef->p);
		//		perimeter += tmpp.dis(p);
		//	}
		}
        if (itr != st.begin()) {
            IT now = itr; now--;
            while (now != st.begin()) {
                IT tmp = now; tmp--;
                if (sgn((tmp->p - p) ^ (now->p - p)) >= 0) {
					tmp->next_p = itr->p;
                    area += (tmp->p - p) ^ (now->p - p);
				    perimeter -= p.dis(now->p);
				    Point tmpp = now->p; 
				    perimeter -= tmpp.dis(tmp->p);
				    perimeter += p.dis(tmp->p);
                    st.erase(now--);
                } else break;
            }
			if (now->p.x == p.x) {
				if (now != st.begin()) {
					IT tmp = now; tmp--;
					tmp->next_p = itr->p;
				}
				perimeter -= p.dis(now->p);
				if ((int)st.size() > 2 && now != st.begin()) {
					IT pre = now;
					if (now == st.begin()) pre = (--st.end());
					else --pre;
					Point tmpp = now->p;
					perimeter -= tmpp.dis(pre->p);
					perimeter += p.dis(pre->p);
				} 
				st.erase(now);
			}
		} 
        if (itr != (--st.end())) {
            IT now = itr; now++;
            while (now != (--st.end())) {
                IT tmp = now; tmp++;
                if (sgn((now->p - p) ^ (tmp->p - p)) >= 0) {
					itr->next_p = tmp->p;
                    area += (now->p - p) ^ (tmp->p - p);
					perimeter -= p.dis(now->p);
					Point tmpp = now->p;
					perimeter -= tmpp.dis(tmp->p);
					perimeter += p.dis(tmp->p);
                    st.erase(now++);
                } else break;
            }
        }
    }
	void insert(db x, db y = 0) { insert(Point(x, y)); } 
	//查询max(ax + by)
    db query(db a, db b) {
		if (size() == 0) return -INF;
        IT it = st.upper_bound(node(Point(a, b), Point(0, 0), 1));
       	return it->p.x * a + b * it->p.y;
    }
};

const int N = 1e5 + 10;
int n, q, m, x, y, exist[N];
pDD p[N]; 
struct E { int op, id; db ans; }e[N];

int main() {
	DCH up;
	scanf("%d%d%d", &n, &x, &y);
	up.insert(0, 0);
	up.insert(n, 0);
	up.insert(x, y);
	scanf("%d", &m);
	for (int i = 1; i <= m; ++i) {
		exist[i] = 1;
		scanf("%lf%lf", &p[i].fi, &p[i].se);
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
		up.insert(p[i].fi, p[i].se); 
	for (int i = q; i >= 1; --i) {
		if (e[i].op == 2)
			e[i].ans = up.perimeter;
		else 
			up.insert(p[e[i].id].fi, p[e[i].id].se);
	}
	for (int i = 1; i <= q; ++i) if (e[i].op == 2)
		printf("%.2f\n", e[i].ans);
    return 0;
}

