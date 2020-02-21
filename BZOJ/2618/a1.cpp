#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
typedef double db;
const db eps = 1e-8;
const db PI = acos(-1.0);
int sgn(db x) { if (fabs(x) < eps) return 0; return x < 0 ? -1 : 1; }

struct Point {
	db x, y;
	Point(db x = 0, db y = 0) : x(x), y(y) {}
	void scan() { db _x, _y; scanf("%lf%lf", &_x, &_y); x = _x, y = _y; }
	void print() { printf("%.11f %.11f\n", x, y); }
	bool operator == (const Point &b) const { return sgn(x - b.x) == 0 && sgn(y - b.y) == 0; }
	bool operator < (const Point &b) const { return sgn(x - b.x) == 0 ? sgn(y - b.y) < 0 : x < b.x; }
	Point operator + (const Point &b) const { return Point(x + b.x, y + b.y); }
	Point operator - (const Point &b) const { return Point(x - b.x, y - b.y); }
	Point operator * (const db &b) const { return Point(x * b, y * b); }
	Point operator / (const db &b) const { return Point(x / b, y / b); }
	db operator ^ (const Point &b) const { return x * b.y - y * b.x; }
	db operator * (const Point &b) const { return x * b.x + y * b.y; }
	db len() { return hypot(x, y); }
	db len2() { return x * x + y * y; }
	db dis(Point b) { return hypot(x - b.x, y - b.y); }
	int quad() {
		int _x = sgn(x), _y = sgn(y);
		if (_x > 0 && _y >= 0) return 1;
		if (_x <= 0 && _y > 0) return 2;
		if (_x < 0 && _y <= 0) return 3;
		if (_x >= 0 && _y < 0) return 4;
	}
	//求PA和PB构成的夹角 lightOJ 1203
	db rad(Point a, Point b) {
		Point p = *this;
		return fabs(atan2(fabs((a - p) ^ (b - p)), (a - p) * (b - p)));
	}
	//化为长度为r的向量
	Point trunc(db r) {
		db l = len();
		if (!sgn(l)) return *this;
		r /= l;
		return Point(x * r, y * r);
	}
	//逆时针旋转90度
	Point rotleft() { return Point(-y, x); }
	//顺时针旋转90度
	Point rotright() { return Point(y, -x); }
	//绕点p旋转angle
	Point rotate(Point p, db angle) {
		Point v = (*this) - p;
		db c = cos(angle), s = sin(angle);
		return Point(p.x + v.x * c - v.y * s, p.y + v.x * s + v.y * c);
	}
};

struct Line {
	Point s, e;
	Line() {}
	Line(Point s, Point e) : s(s), e(e) {}
	void scan() { s.scan(); e.scan(); }
	void print() { s.print(); e.print(); }
	bool operator == (const Line &b) const { return s == b.s && e == b.e; }
	//根据一个点和倾斜角确定直线,0 <= angle <= PI
	Line(Point p, db angle) {
		s = p;
		if (sgn(angle - PI / 2) == 0) {
			e = (s + Point(0, 1));
		} else {
			e = (s + Point(1, tan(angle)));
		}
	}
	//ax + by + c = 0
	Line(db a, db b, db c) {
		if (sgn(a) == 0) {
			s = Point(0, -c / b);
			e = Point(1, -c / b);
		} else if (sgn(b) == 0) {
			s = Point(-c / a, 0);
			e = Point(-c / a, 1);
		} else {
			s = Point(0, -c / b);
			e = Point(1, (-c - a) / b);
		}
	}
	void adjust() { if (e < s) swap(s, e); }
	db length() { return s.dis(e); }
	//返回直线倾斜角 0 <= angle <= PI
	db angle() {
		db k = atan2(e.y - s.y, e.x - s.x);
		if (sgn(k) < 0) k += PI;
		if (sgn(k - PI) == 0) k -= PI;
		return k;
	}
	//点和直线关系
	//1 在左侧
	//2 在右侧
	//3 在直线上
	int relationPoint(Point p) {
		int c = sgn((p - s) ^ (e - s));
		if (c < 0) return 1;
		if (c > 0) return 2;	
		return 3;
	}
	//判断点是否在线段上
	bool pointOnSeg(Point p) { return sgn((p - s) ^ (e - s)) == 0 && sgn((p - s) * (p - e)) <= 0; }
	//判断两向量是否平行
	bool parallel(Line b) { return sgn((e - s) ^ (b.e - b.s)) == 0; }
	//两线段相交判断
	//2 规范相交
	//1 非规范相交
	//0 不相交
	int segCrossSeg(Line b) {
		int d1 = sgn((e - s) ^ (b.s - s));
		int d2 = sgn((e - s) ^ (b.e - s));
		int d3 = sgn((b.e - b.s) ^ (s - b.s));
		int d4 = sgn((b.e - b.s) ^ (e - b.s));
		if ((d1 ^ d2) == -2 && (d3 ^ d4) == -2) return 2;
		return ((d1 == 0 && sgn((b.s - s) * (b.s - e)) <= 0) ||
				(d2 == 0 && sgn((b.e - s) * (b.e - e)) <= 0) ||
				(d3 == 0 && sgn((s - b.s) * (s - b.e)) <= 0) ||
				(d4 == 0 && sgn((e - b.s) * (e - b.e)) <= 0));
	}
	//直线和线段相交判断
	//2 规范相交
	//1 非规范相交
	//0 不相交
	int lineCrossSeg(Line b) {
		int d1 = sgn((e - s) ^ (b.s - s));
		int d2 = sgn((e - s) ^ (b.e - s));
		if ((d1 ^ d2) == -2) return 2;
		return (d1 == 0 || d2 == 0);
	}
	//两直线关系
	//0 平行
	//1 重合
	//2 相交
	int lineCrossLine(Line b) {
		if ((*this).parallel(b)) return b.relationPoint(s) == 3;
		return 2;
	}
	//求两直线交点
	//要保证两直线不平行或重合
	Point crossPoint(Line b) {
		db a1 = (b.e - b.s) ^ (s - b.s);
		db a2 = (b.e - b.s) ^ (e - b.s);
		return Point((s.x * a2 - e.x * a1) / (a2 - a1), (s.y * a2 - e.y * a1) / (a2 - a1));
	}
	//点到直线的距离
	db disPointToLine(Point p) { return fabs((p - s) ^ (e - s)) / length(); } 
	//点到线段的距离
	db disPointToSeg(Point p) {
		if (sgn((p - s) * (e - s)) < 0 || sgn((p - e) * (s - e)) < 0)
			return min(p.dis(s), p.dis(e));
		return disPointToLine(p);
	}
	//线段到线段的距离
	//如果两线段相交，距离为0
	db disSegToSeg(Line b) {
		return min(min(disPointToSeg(b.s), disPointToSeg(b.e)),
				   min(b.disPointToSeg(s), b.disPointToSeg(e)));
	}
	//返回点p在直线上的投影
	Point lineProg(Point p) { return s + (((e - s) * ((e - s) * (p - s))) / ((e - s).len2())); }
	//返回点p关于直线的对称点
	Point symmetryPoint(Point p) {
		Point q = lineProg(p);
		return Point(q.x * 2 - p.x, q.y * 2 - p.y);
	}
};

struct Circle {
	Point p; db r;
	Circle() {}
	Circle(Point p, db r) : p(p), r(r) {}
	Circle(db x, db y, db r) : p(Point(x, y)), r(r) {}
	//三角形的相关圆
	//外接圆 opt = 0 利用两条边的中垂线得到圆心
	//内切圆 opt = 1 
	//UVA 12304
	Circle(Point a, Point b, Point c, int opt) {
		if (opt == 0) {
			Line u = Line((a + b) / 2, ((a + b) / 2 + ((b - a).rotleft())));
			Line v = Line((b + c) / 2, ((b + c) / 2 + ((c - b).rotleft())));
			p = u.crossPoint(v);
			r = p.dis(a);
		} else {
			Line u, v;
			db m = atan2(b.y - a.y, b.x - a.x), n = atan2(c.y - a.y, c.x - a.x);
			u.s = a;
			u.e = u.s + Point(cos((n + m) / 2), sin((n + m) / 2));
			v.s = b;
			m = atan2(a.y - b.y, a.x - b.x), n = atan2(c.y - b.y, c.x - b.x);
			v.e = v.s + Point(cos((n + m) / 2), sin((n + m) / 2));
			p = u.crossPoint(v);
			r = Line(a, b).disPointToSeg(p);
		}
	}	
	void scan() { p.scan(); scanf("%lf", &r); }
	void print() { printf("%.10f %.10f %.10f\n", p.x, p.y, r); }
	bool operator == (const Circle &b) const { return (p == b.p) && sgn(r - b.r) == 0; }
	bool operator < (const Circle &b) const { return ((p < b.p) || ((p == b.p) && sgn(r - b.r) < 0)); }
	db area() { return PI * r * r; }
	db circumference() { return PI * r * 2; }
	//点和圆的关系
	//0 圆外
	//1 圆上
	//2 圆内
	int relationPoint(Point b) {
		db dis = b.dis(p);
		if (sgn(dis - r) < 0) return 2;
		if (sgn(dis - r) == 0) return 1;
		return 0;
	}
	//线段和圆的关系
	//比较的是圆心到线段的距离和半径的关系
	int relationSeg(Line b) {
		db dis = b.disPointToSeg(p);
		if (sgn(dis - r) < 0) return 2;
		if (sgn(dis - r) == 0) return 1;
		return 0;
	}
	//直线和圆的关系
	//比较的是圆心到直线的距离和半径的关系
	int relationLine(Line b) {
		db dis = b.disPointToLine(p);
		if (sgn(dis - r) < 0) return 2;
		if (sgn(dis - r) == 0) return 1;
		return 0;
	}
	//两圆的关系
	//5 相离
	//4 外切
	//3 相交
	//2 内切
	//1 内含
	//UVA12304
	int relationCircle(Circle b) {
		db dis = p.dis(b.p);
		if (sgn(dis - r - b.r) > 0) return 5;
		if (sgn(dis - r - b.r) == 0) return 4;
		db l = fabs(r - b.r);
		if (sgn(dis - r - b.r) && sgn(dis - l) > 0) return 3;
		if (sgn(dis - l) == 0) return 2;
		if (sgn(dis - l) < 0) return 1;
		//不可达分支
	    return 0;	
	}
	//求直线和圆的交点 返回值为交点个数
	int pointCrossLine(Line b, Point &p1, Point &p2) {
		if (!(*this).relationLine(b)) return 0;
		Point a = b.lineProg(p);
		db d = b.disPointToLine(p);
		d = sqrt(r * r - d * d);
		if (sgn(d) == 0) {
			p1 = p2 = a;
			return 1;
		}
		p1 = a + (b.e - b.s).trunc(d);
		p2 = a - (b.e - b.s).trunc(d);
		return 2;
	}
	//求两个圆的交点 返回值为交点个数
	//UVA12304
	int pointCrossCircle(Circle b, Point &p1, Point &p2) {
		int rel = relationCircle(b);
		if (rel == 1 || rel == 5) return 0;
		db d = p.dis(b.p);
		db l = (d * d + r * r - b.r * b.r) / (d * 2);
	    db h = sqrt(r * r - l * l);
		Point tmp = p + (b.p - p).trunc(l);
		p1 = tmp + ((b.p - p).rotleft().trunc(h));
		p2 = tmp + ((b.p - p).rotright().trunc(h));
		if (rel == 2 || rel == 4) return 1;
		return 2;
	}
	//过一点作圆的切线(先判断点和圆的关系) 返回切线条数
	//UVA12304
	int tangentLine(Point q, Line &u, Line &v) {
		int x = relationPoint(q);
		if (x == 2) return 0;
		if (x == 1) {
			u = Line(q, q + (q - p).rotleft());
			v = u;
			return 1;
		}
		db d = p.dis(q);
		db l = r * r / d;
		db h = sqrt(r * r - l * l);
		u = Line(q, p + ((q - p).trunc(l) + (q - p).rotleft().trunc(h)));
		v = Line(q, p + ((q - p).trunc(l) + (q - p).rotright().trunc(h)));
		return 2;
	}
	//得到与直线u相切, 过点q, 半径为r1的圆
	//UVA12304
	static int getCircle(Line u, Point q, db r1, Circle &c1, Circle &c2) {
		db dis = u.disPointToLine(q);
		if (sgn(dis - r1 * 2) > 0) return 0;
		if (sgn(dis) == 0) {
			c1.p = q + ((u.e - u.s).rotleft().trunc(r1));
			c2.p = q + ((u.e - u.s).rotright().trunc(r1));
			c1.r = c2.r = r1;
			return 2;
		}
		Line u1 = Line((u.s + (u.e - u.s).rotleft().trunc(r1)), (u.e + (u.e - u.s).rotleft().trunc(r1)));
		Line u2 = Line((u.s + (u.e - u.s).rotright().trunc(r1)), (u.e + (u.e - u.s).rotright().trunc(r1)));
		Circle cc = Circle(q, r1);
		Point p1, p2;
		if (!cc.pointCrossLine(u1, p1, p2)) cc.pointCrossLine(u2, p1, p2);
		c1 = Circle(p1, r1);
		if (p1 == p2) {
			c2 = c1;
			return 1;
		}
		c2 = Circle(p2, r1);
		return 2;
	}
	//同时与直线u, v相切, 半径为r1的圆
    static int getCircle(Line u, Line v, db r1, Circle &c1, Circle &c2, Circle &c3, Circle &c4){
        if(u.parallel(v)) return 0;
        Line u1 = Line(u.s + (u.e - u.s).rotleft().trunc(r1), u.e + (u.e - u.s).rotleft().trunc(r1));
        Line u2 = Line(u.s + (u.e - u.s).rotright().trunc(r1), u.e + (u.e - u.s).rotright().trunc(r1));
        Line v1 = Line(v.s + (v.e - v.s).rotleft().trunc(r1), v.e + (v.e - v.s).rotleft().trunc(r1));
        Line v2 = Line(v.s + (v.e - v.s).rotright().trunc(r1), v.e + (v.e - v.s).rotright().trunc(r1));
        c1.r = c2.r = c3.r = c4.r = r1;
        c1.p = u1.crossPoint(v1);
        c2.p = u1.crossPoint(v2);
        c3.p = u2.crossPoint(v1);
        c4.p = u2.crossPoint(v2);
        return 4;
    }
	//同时与不相交圆cx, cy相切, 半径为r1的圆
	//UVA12304
	static int getCircle(Circle cx, Circle cy, db r1, Circle &c1, Circle &c2) {
		Circle x(cx.p, r1 + cx.r), y(cy.p, r1 + cy.r);
		int t = x.pointCrossCircle(y, c1.p, c2.p);
		if (!t) return 0;
		c1.r = c2.r = r1;
		return t;
	}
	//得到过a, b两点，半径为r1的两个圆
	static int getCircle(Point a, Point b, db r1, Circle &c1, Circle &c2) {
		Circle x(a, r1), y(b, r1);
		int t = x.pointCrossCircle(y, c1.p, c2.p);
		if (!t) return 0;
		c1.r = c2.r = r1;
		return t;
	}
	//求两圆相交面积
	db areaIntersectCircle(Circle b) {
		int rel = relationCircle(b);
		if (rel >= 4) return 0.0;
		if (rel <= 2) return min(area(), b.area());
		db d = p.dis(b.p);
		db hf = (r + b.r + d) / 2.0;
		db ss = sqrt(hf * (hf - r) * (hf - b.r) * (hf - d)) * 2.0;
		db a1 = acos((r * r + d * d - b.r * b.r) / (2.0 * r * d)) * r * r;
		db a2 = acos((b.r * b.r + d * d - r * r) / (2.0 * b.r * d)) * b.r * b.r;
		return a1 + a2 - ss;	
	}
	//求圆和三角形pab的相交面积
	//POJ 3675 HDU 3982 HDU 2892
	db areaIntersectTriangle(Point a, Point b) {
		if (sgn((p - a) ^ (p - b)) == 0) return 0.0;
		Point q[5];
		int len = 0;
		q[len++] = a;
		Line l(a, b);
		Point p1, p2;
		if (pointCrossLine(l, q[1], q[2]) == 2) {
			if (sgn((a - q[1]) * (b - q[1])) < 0) q[len++] = q[1];
			if (sgn((a - q[2]) * (b - q[2])) < 0) q[len++] = q[2];
		}
		q[len++] = b;
		if (len == 4 && sgn((q[0] - q[1]) * (q[2] - q[1])) > 0) swap(q[1], q[2]);
		db res = 0;
		for (int i = 0; i < len - 1; ++i) {
			if (relationPoint(q[i]) == 0 || relationPoint(q[i + 1]) == 0) {
				db arg = p.rad(q[i], q[i + 1]);
				res += r * r * arg / 2.0;
			} else {
				res += fabs((q[i] - p) ^ (q[i + 1] - p)) / 2.0;
			}
		}
		return res;
	}
};

struct Polygon {
	vector <Point> p;
	Polygon() { p.clear(); }
	int sze() { return p.size(); }
	Point& operator[](int x) { return p[x]; }
	void add(Point q) { p.push_back(q); }
	void scan(int n = -1) { if (n == -1) scanf("%d", &n); p.resize(n); for (int i = 0; i < n; ++i) p[i].scan(); }
	vector<Line> getline() { 
		vector <Line> l(sze());
		for (int i = 0; i < sze(); ++i) {
			int j = (i + 1) % sze();
			l[i] = Line(p[i], p[j]);
		}
		return l;
	}
	//极角排序
	//POJ 2007
	struct cmpNorm {
		Point p;
		cmpNorm(Point p) : p(p) {}
		bool operator () (Point a, Point b) {
			int d = sgn((a - p) ^ (b - p));
			if (d == 0) {
				return sgn(a.dis(p) - b.dis(p) < 0);
			} else {
				return d > 0;
			}
		}
	};
	void norm() {
		Point mi = *p.begin();
		for (int i = 1; i < sze(); ++i) mi = min(mi, p[i]);
		sort(p.begin(), p.end(), cmpNorm(mi)); 
	}
	void norm(Point mi) {
		sort(p.begin(), p.end(), cmpNorm(mi));
	}
	//Andrw 求凸包
	//opt=1 严格 不会有三点共线
	//opt=0 非严格 有三点共线
	//LightOJ 1203
	void convexhull(int opt = 1) { 
		sort(p.begin(), p.end());
		Polygon res; res.p.resize(sze() * 2);
		int top = 0;
	    for (int i = 0; i < sze(); ++i) {
			while (top > 1 && sgn((res.p[top - 1] - res.p[top - 2]) ^ (p[i] - res.p[top - 2])) < opt) --top;
			res[top++] = p[i];
	    }
	    int k = top; 
	    for (int i = sze() - 2; i >= 0; --i) {
			while (top > k && sgn((res.p[top - 1] - res.p[top - 2]) ^ (p[i] - res.p[top - 2])) < opt) --top;
			res[top++] = p[i];
	    }
	    if (sze() > 1) --top;
		res.p.resize(top);
		p = res.p;
	}
	//计算周长
	//LightOJ 1239
	db getCircumference() {
		db res = 0;
		for (int i = 0; i < sze(); ++i) {
			int j = (i + 1) % sze();
			res += p[i].dis(p[j]);
		}
		return res;
	}
	//计算有向面积
	//顺时针 负 逆时针 正
	db getArea() {
		db res = 0;
		for (int i = 0; i < sze(); ++i) {
			int j = (i + 1) % sze();
			res += (p[i] ^ p[j]);
		}
		return res / 2;
	}
	//得到方向
	//1 逆时针 0 顺时针
	bool getDir() { return sgn(getArea()) > 0; }
	//得到重心
	Point getBarycenter() {
		Point res(0, 0);
		db area = 0;
		for (int i = 1; i < sze() - 1; ++i) {
			db tmp = (p[i] - p[0]) ^ (p[i + 1] - p[0]);
			if (sgn(tmp) == 0) continue;
			area += tmp;
			res.x += (p[0].x + p[i].x + p[i + 1].x) / 3 * tmp;
			res.y += (p[0].y + p[i].y + p[i + 1].y) / 3 * tmp;
		}
		if (sgn(area)) res = res / area;
		return res;
	}
	//判断是不是凸多边形
	//HDU 2108
	bool isconvex() {
		bool s[3] = {0, 0};
		for (int i = 0; i < sze(); ++i) {
			int j = (i + 1) % sze();
			int k = (j + 1) % sze();
			s[sgn((p[j] - p[i]) ^ (p[k] - p[i])) + 1] = true;
			if (s[0] && s[2]) return false;
		}
		return true;
	}
	//判断点和任意多边形的关系
	//3 点上
	//2 边上
	//1 内部
	//0 外部
	int relationPoint(Point q) {
		for (int i = 0; i < sze(); ++i) {
			if (p[i] == q) return 3;
		}
		vector<Line> l(getline());
		for (int i = 0; i < (int)l.size(); ++i) {
			if (l[i].pointOnSeg(q)) return 2;
		}
		int cnt = 0;
		for (int i = 0; i < sze(); ++i) {
			int j = (i + 1) % sze();
			int k = sgn((q - p[j]) ^ (p[i] - p[j]));
			int u = sgn(p[i].y - q.y);
			int v = sgn(p[j].y - q.y);
			if (k > 0 && u < 0 && v >= 0) cnt++;
			if (k < 0 && v < 0 && u >= 0) cnt--;
		}
		return cnt != 0;
	}
	//直线u切割凸多边形左侧
	//注意直线方向
	//HDU 3982
	Polygon convexCut(Line u) {
		Polygon res;
		for (int i = 0; i < sze(); ++i) {
			int j = (i + 1) % sze();
			int d1 = sgn((u.e - u.s) ^ (p[i] - u.s));
			int d2 = sgn((u.e - u.s) ^ (p[j] - u.s));
			if (d1 >= 0) res.add(p[i]);
			if (d1 * d2 < 0) res.add(u.crossPoint(Line(p[i], p[j])));
		}	
		return res;
	}
	//多边形和圆交的面积
	//POJ 3675 HDU 2983 HDU 2892
	db areaIntersectCircle(Circle c) {
		db res = 0;
		for (int i = 0; i < sze(); ++i) {
			int j = (i + 1) % sze();
			if (sgn((p[j] - c.p) ^ (p[i] - c.p)) >= 0) {
				res += c.areaIntersectTriangle(p[i], p[j]);
			} else {
				res -= c.areaIntersectTriangle(p[i], p[j]);
			}
		}
		return fabs(res);
	}	
	//多边形和圆的关系
	//2 圆完全在多边形内
	//1 圆在多边形里面, 碰到了多边形边界
	//0 其它
	int relationCircle(Circle c) {
		vector<Line>l(getline());
		int x = 2;
		if (relationPoint(c.p) != 1) return 0; //圆心不在内部
		for (int i = 0; i < sze(); ++i) {
			if (c.relationSeg(l[i]) == 2) return 0;
			if (c.relationSeg(l[i]) == 1) return 1;
		}
		return x;
	}
};

struct halfplane:public Line {
	db angle;
	//表示向量s -> e 逆时针(左侧)的半平面
	halfplane() {}
	halfplane(Point _s, Point _e) { s = _s, e = _e; }
	halfplane(Line v) { s = v.s, e = v.e; } 
	void calcangle() { angle = atan2(e.y - s.y, e.x - s.x); }
	bool operator < (const halfplane &b) const { return angle < b.angle; }
};

struct halfplanes {
	vector <halfplane> hps, deq; 
	int st, ed;
	halfplane& operator[] (int x) { return hps[x]; }
	void add(halfplane hp) { hps.push_back(hp); }
	int sze() { return hps.size(); }
	void unique() {
		int m = 1;
		for (int i = 1; i < sze(); ++i) {
			if (sgn(hps[i].angle - hps[i - 1].angle) != 0) {
				hps[m++] = hps[i];
			} else if (sgn((hps[m - 1].e - hps[m - 1].s) ^ (hps[i].s - hps[m - 1].s)) > 0) {
				hps[m - 1] = hps[i];
			}
		} 
		hps.resize(m);
	}
	bool halfPlaneIntersect() { 
		if (sze() < 2) return false;
		for (int i = 0; i < sze(); ++i) hps[i].calcangle(); 
		sort(hps.begin(), hps.end()); unique();	
		deq.resize(sze() + 5); st = 1, ed = 2;
		deq[1] = hps[0]; deq[2] = hps[1];
		for (int i = 2; i < sze(); ++i) {
			while (st < ed && sgn((hps[i].e - hps[i].s) ^ (deq[ed].crossPoint(deq[ed - 1]) - hps[i].s)) < 0) --ed;
			while (st < ed && sgn((hps[i].e - hps[i].s) ^ (deq[st].crossPoint(deq[st + 1]) - hps[i].s)) < 0) ++st;
			deq[++ed] = hps[i];
		}
		while (st < ed && sgn((deq[st].e - deq[st].s) ^ (deq[ed].crossPoint(deq[ed - 1]) - deq[st].s)) < 0) --ed;
		while (st < ed && sgn((deq[ed].e - deq[ed].s) ^ (deq[st].crossPoint(deq[st + 1]) - deq[ed].s)) < 0) ++st;
		if (st + 1 >= ed) return false;
		return true;
	}
	Polygon getConvex() {
		deq[st - 1] = deq[ed];
		Polygon po; 
		for (int i = st; i <= ed; ++i) 
			po.add(deq[i].crossPoint(deq[i - 1]));
		return po;
	}
};

int main() {
	halfplanes hps; 
	int n; scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		Polygon po; po.scan(); 
		for (int j = 0; j < po.sze(); ++j) {
			int k = (j + 1) % po.sze(); 
			hps.add(halfplane(po[j], po[k]));
		}
	}
	hps.halfPlaneIntersect();
	printf("%.3f\n", hps.getConvex().getArea());
	return 0;
}
