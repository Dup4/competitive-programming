#include <bits/stdc++.h>
using namespace std;

typedef long long db;
const db eps = 1e-10;
const db PI = acos(-1.0); 
//long long类型时使用
int sgn(db x) { if (x == 0) return 0; return x < 0 ? -1 : 1; }
//int sgn(db x) { if (fabs(x) < eps) return 0; return x < 0 ? -1 : 1; }
db sqr(db x) { return x * x; }
db fixOut(db x) { if (sgn(x) == 0) return 0; return x; }
db toRad(db angle) { return angle / 180 * PI; }

struct Point {
	db x, y;
	Point(db x = 0, db y = 0) : x(x), y(y) {}
	void scan() { db _x, _y; scanf("%lld%lld", &_x, &_y); x = _x, y = _y; }
	void print() { printf("%.11f %.11f\n", x, y); }
	bool operator == (const Point &b) const { return sgn(x - b.x) == 0 && sgn(y - b.y) == 0; }
	bool operator < (const Point &b) const { return sgn(x - b.x) == 0 ? sgn(y - b.y) < 0 : x < b.x; }
	Point operator + (const Point &b) const { return Point(x + b.x, y + b.y); }
	Point operator - (const Point &b) const { return Point(x - b.x, y - b.y); }
	Point operator * (const db &b) const { return Point(x * b, y * b); }
	Point operator / (const db &b) const { return Point(x / b, y / b); }
	db operator ^ (const Point &b) const { return x * b.y - y * b.x; }
	db operator * (const Point &b) const { return x * b.x + y * b.y; }
	db len() { return norm(complex<db>(x, y)); }
	db len2() { return x * x + y * y; }
	db dis(Point b) { return norm(complex<db>(x - b.x, y - b.y)); }
	db dis2(Point b) { return (x - b.x) * (x - b.x) + (y - b.y) * (y - b.y); }
	int quad() {
		int _x = sgn(x), _y = sgn(y);
		if (_x > 0 && _y >= 0) return 1;
		if (_x <= 0 && _y > 0) return 2;
		if (_x < 0 && _y <= 0) return 3;
		if (_x >= 0 && _y < 0) return 4;
	}
	//求PA和PB构成的夹角 lightOJ 1203
	db getRad(Point a, Point b) {
		Point p = *this;
		return fabs(atan2(fabs((a - p) ^ (b - p)), (a - p) * (b - p)));
	}
	//单位法向量
	Point normal() { return Point(-y, x) / len(); }
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
	//绕点p旋转rad弧度
	Point rotate(Point p, db rad) {
		Point v = (*this) - p;
		db c = cos(rad), s = sin(rad);
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
	Line(Point p, db rad) {
		s = p;
		if (sgn(rad - PI / 2) == 0) {
			e = (s + Point(0, 1));
		} else {
			e = (s + Point(1, tan(rad)));
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
	//返回直线倾斜角 0 <= rad <= PI
	db getAngle() {
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

struct Polygon {
	vector <Point> p;
	Polygon() { p.clear(); }
	Polygon(int n) { p.clear(); p.resize(n); }
	int sze() { return p.size(); }
	Point& operator[](int x) { return p[(x + sze()) % sze()]; }
	void add(Point q) { p.push_back(q); }
	void scan(int n = -1) { if (n == -1) scanf("%d", &n); (*this) = Polygon(n); for (int i = 0; i < n; ++i) p[i].scan(); }
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
	void norm(Point mi) { sort(p.begin(), p.end(), cmpNorm(mi)); }
	//Andrw 求凸包
	//opt=1 严格 不会有三点共线
	//opt=0 非严格 有三点共线
	//LightOJ 1203
	//凸包上的点不超过sqrt(m), m为坐标系范围
	void convexHull(int opt = 1) {
		sort(p.begin(), p.end());
		Polygon res; res.p.resize(sze() * 2);
		int top = -1;
	    for (int i = 0; i < sze(); ++i) {
			while (top > 0 && sgn((res[top] - res[top - 1]) ^ (p[i] - res[top - 1])) < opt) --top;
			res[++top] = p[i];
	    }
	    int pre = top; 
	    for (int i = sze() - 2; i >= 0; --i) {
			while (top > pre && sgn((res[top] - res[top - 1]) ^ (p[i] - res[top - 1])) < opt) --top;
			res[++top] = p[i];
	    }
		if (top > 0) res.p.resize(top);
		p = res.p;
	}
	//判断是不是凸多边形
	//HDU 2108
	bool isConvex() {
		bool s[3] = {0, 0};
		for (int i = 0; i < sze(); ++i) {
			int j = (i + 1) % sze();
			int k = (j + 1) % sze();
			s[sgn((p[j] - p[i]) ^ (p[k] - p[i])) + 1] = true;
			if (s[0] && s[2]) return false;
		}
		return true;
	}
	//判断点和凸包的关系 O(log n)
	//1 边上
	//0 内部
	//-1 外部
	//UVA 10256
	int pointInConvex(Point q) {
		int l = 1, r = sze() - 2;
		while (r - l >= 0) {
			int mid = (l + r) >> 1;
			int a1 = sgn((p[mid] - p[0]) ^ (q - p[0]));
			int a2 = sgn((p[mid + 1] - p[0]) ^ (q - p[0]));
			if (a1 >= 0 && a2 <= 0) {
				int a3 = sgn((q - p[mid]) ^ (q - p[mid + 1]));
				if (a3 < 0) return -1;
				else if (a1 || a2 || a3) return 0;
				return 1;
			} else if (a1 < 0) {
				r = mid - 1;
			} else {
				l = mid + 1;
			}
		}
		return -1;
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
	//判断两凸包是否有交点
	//UVA 10256
	bool ConvexPolygonDisjoint(Polygon &b) { 
	    for (int i = 0; i < sze(); ++i)
		   	if (b.relationPoint(p[i]) > 0)	
				return true;
	    for (int i = 0; i < b.sze(); ++i)
			if (relationPoint(b[i]) > 0)
				return true;
	    for (int i = 0; i < sze(); ++i)
	        for(int j = 0; j < b.sze(); ++j) {
				int _i = (i + 1) % sze();
				int _j = (j + 1) % b.sze();
				if (Line(p[i], p[_i]).segCrossSeg(Line(b[j], b[_j])))
					return true;
			}
	    return false;
	}
};

int main() {
	int _T; scanf("%d", &_T);
	while (_T--) {
		Polygon po[2];
		int n; scanf("%d", &n);
		for (int i = 1, y; i <= n; ++i) {
			Point q; q.scan();
			scanf("%d", &y);
			if (y == -1) ++y;
			po[y].add(q);
		}
		puts(po[0].ConvexPolygonDisjoint(po[1]) ? "Infinite loop!" : "Successful!");
	}
	return 0;
}
