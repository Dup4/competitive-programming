#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
typedef double db;
const db eps = 1e-10;
const db PI = acos(-1.0); 
int sgn(db x) { if (fabs(x) < eps) return 0; return x < 0 ? -1 : 1; }
db fixOut(db x) { if (sgn(x) == 0) return 0; return x; }
db toRad(db angle) { return angle / 180 * PI; }

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
	//返回点集直径的平方 需要先求凸包
	//POJ 2187
	db convexDimmeter2() {
	    if (sze() == 1) return 0;
	    if (sze() == 2) return p[0].dis2(p[1]);
	    db ans = 0;
	    for (int u = 0, v = 1; u < sze(); ++u) {
	        //一条直线贴住边p[u] - p[u + 1]
	        while (1) {
	            // 当Area(p[u], p[u + 1], p[v + 1]) <= Area(p[u], p[u + 1], p[v])时停止旋转
	            // 即Cross(p[u + 1] - p[u], p[v + 1] - p[u]) - Cross(p[u + 1] - p[u], p[v] - p[u]) <= 0
	            // 根据Cross(A, B) - Cross(A, C) = Cross(A, B - C)
	            // 化简得Cross(p[u + 1] - p[u], p[v + 1] - p[v]) <= 0
				int diff = sgn((p[(u + 1) % sze()] - p[u]) ^ (p[(v + 1) % sze()] - p[v]));
				if (diff <= 0) { 
					// u 和 v 是对踵点
	                ans = max(ans, p[u].dis2(p[v]));
					//diff == 0 时 u 和 v + 1也是对踵点
					if (diff == 0) ans = max(ans, p[u].dis2(p[(v + 1) % sze()]));
	                break;
	            }
	            v = (v + 1) % sze();
	        }
	    }
	    return ans;
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
	//HDU 1115
	Point getBarycenter() {
		Point res(0, 0);
		db area = 0;
		for (int i = 1; i < sze() - 1; ++i) {
			db tmp = (p[i] - p[0]) ^ (p[i + 1] - p[0]);
			if (sgn(tmp) == 0) continue;
			area += tmp;
			res.x += (p[0].x + p[i].x + p[i + 1].x) * tmp;
			res.y += (p[0].y + p[i].y + p[i + 1].y) * tmp;
		}
		if (sgn(area)) res = res / (area * 3);
		return res;
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
	//向量u切割凸多边形
	//注意向量方向 保留的是向量左边的部分
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
	//判断两凸包是否有交点
	//UVA 10256
	bool ConvexPolygonDisjoint(Polygon &b) { 
	    for (int i = 0; i < sze(); ++i) 
			if (b.pointInConvex(p[i]) >= 0) 
				return true;
	    for (int i = 0; i < b.sze(); ++i)
			if (pointInConvex(b[i]) >= 0)
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
	//两凸包最值距离
	//求最大 就将Min改成Max即可
	//POJ 3608
	db disConvexToConvex(Polygon &q) {
		int _p = 0, _q = 0;
	    for (int i = 1; i < sze(); ++i)
			if (sgn(p[i].y - p[_p].y) < 0) _p = i;
	    for (int i = 1; i < q.sze(); ++i)
			if (sgn(q[i].y - q[_q].y) > 0) _q = i;
	    db ans = p[_p].dis(q[_q]); 
	    for(int i = 0; i < sze(); ++i) {
			while (1) {
				int diff = sgn(((p[(_p + 1) % sze()] - p[_p]) ^ (q[(_q + 1) % q.sze()] - p[_p])) - ((p[(_p + 1) % sze()] - p[_p]) ^ (q[_q] - p[_p])));
				if (diff > 0) {
					_q = (_q + 1) % q.sze();
					continue;
				}
				ans = min(ans, Line(p[_p], p[(_p + 1) % sze()]).disPointToSeg(q[_q]));
				ans = min(ans, Line(p[_p], p[(_p + 1) % sze()]).disSegToSeg(Line(q[_q], q[(_q + 1) % q.sze()])));
				ans = min(ans, p[_p].dis(q[_q]));
				ans = min(ans, p[_p].dis(q[(_q + 1) % q.sze()]));
				_p = (_p + 1) % sze();
				break;
			}
	    }
	    return ans;
	}
	//凸包最大内接三角形面积 O(n^2)
	//HDU2202 CF682E
	Polygon convexMaxInnerTriangle() {
	    if (sze() < 3) return Polygon();
	    Polygon res(3);	
		db ans = 0;
	    for(int i = 0, j, k; i < sze(); ++i) {
	        j = (i + 1) % sze();
	        k = (j + 1) % sze();
	        while((j != k) && (k != i)) {
	            while(sgn(((p[j] - p[i]) ^ (p[(k + 1) % sze()] - p[i])) - ((p[j] - p[i]) ^ (p[k] - p[i]))) > 0) k = (k + 1) % sze();
	            db tmp = (p[j] - p[i]) ^ (p[k] - p[i]);
	            if(tmp > ans) {
					res[0] = p[i]; res[1] = p[j]; res[2] = p[k];
	                ans = tmp;
	            }
	            j = (j + 1) % sze();
	        }
	    }
		return res;
	}
	//凸包最小矩形覆盖
	//返回的矩形的点以逆时针给出
	//LuoguP3187 HDU5251
	Polygon convexMinRectangleCover() {
		Polygon res(4);
	    db area = 1e18;
	    int l = 1, r = 1, u = 1; 
	    for (int i = 0; i < sze(); ++i) {
			int _i = (i + 1) % sze(); 
	        while (sgn(((p[_i] - p[i]) ^ (p[u] - p[i])) - ((p[_i] - p[i]) ^ (p[(u + 1) % sze()] - p[i]))) < 0) u = (u + 1) % sze(); 
			while (sgn((p[_i] - p[i]) * (p[r] - p[i]) - (p[_i] - p[i]) * (p[(r + 1) % sze()] - p[i])) <= 0) r = (r + 1) % sze();
			if (i == 0) l = r;
			while (sgn((p[_i] - p[i]) * (p[l] - p[i]) - (p[_i] - p[i]) * (p[(l + 1) % sze()] - p[i])) > 0) l = (l + 1) % sze();
	        Point A = Line(p[i], p[_i]).lineProg(p[l]);
			Point B = Line(p[i], p[_i]).lineProg(p[r]);
			Point v = (p[_i] - p[i]).rotleft().trunc(1);
			db w = (B - A).len(), h = Line(p[i], p[_i]).disPointToLine(p[u]);
	        Point C = B + v * h;
	        Point D = A + v * h;
	        if (sgn(w * h - area) < 0) {
	            area = w * h;
				res[0] = A; res[1] = B; res[2] = C; res[3] = D;
	        }
	    }
		return res;
	}
};

namespace PolyUninArea {
	db Seg(Point O, Point A, Point B) {
	    if (sgn(B.x - A.x) == 0) return (O.y - A.y) / (B.y - A.y);
	    return (O.x - A.x) / (B.x - A.x);
	}
	db gao(vector <Polygon> poly) {
		int n = poly.size();
		vector <pair<db, int> > s;
	    db res = 0;
	    for (int i = 0; i < n; ++i) {
	        int sz = poly[i].sze();
	        for (int j = 0; j < sz; ++j) {
				s.clear(); 
				s.push_back(make_pair(0, 0));
				s.push_back(make_pair(1, 0));
	            Point a = poly[i].p[j], b = poly[i].p[(j + 1) % sz];
	            for (int k = 0; k < n; ++k) {
	                if (i != k) {
	                    int sz2 = poly[k].sze();
	                    for (int ii = 0; ii < sz2; ++ii) {
	                        Point c = poly[k].p[ii], d = poly[k].p[(ii + 1) % sz2];
	                        int c1 = sgn((b - a) ^ (c - a));
	                        int c2 = sgn((b - a) ^ (d - a));
	                        if (c1 == 0 && c2 == 0) {
	                            if (sgn((b - a) * (d - c))) {
									s.push_back(make_pair(Seg(c, a, b), 1));
									s.push_back(make_pair(Seg(c, a, b), -1));
	                            }
	                        } else {
	                            db s1 = (d - c) ^ (a - c);
	                            db s2 = (d - c) ^ (b - c);
	                            if (c1 >= 0 && c2 < 0) s.push_back(make_pair(s1 / (s1 - s2), 1));
	                            else if (c1 < 0 && c2 >= 0) s.push_back(make_pair(s1 / (s1 - s2), -1));
	                        }
	                    }
	                }
	            }
	            sort(s.begin(), s.end());
	            db pre = min(max(s[0].first, (db)0.0), (db)1.0), now, sum = 0;
	            int cov = s[0].second;
	            for (int j = 1; j < (int)s.size(); ++j) {
	                now = min(max(s[j].first, (db)0.0), (db)1.0);
	                if (!cov) sum += now - pre;
	                cov += s[j].second;
	                pre = now;
	            }
	            res += (a ^ b) * sum; 
	        }
	    }
	    return fabs(res / 2);
	}
}

int main() {
	int n;
    while (scanf("%d", &n) != EOF) {
		vector <Polygon> poly;
		poly.resize(n);
        for (int i = 0; i < n; ++i) {
			poly[i].scan(3);
        	if (poly[i].getDir() == 0)
				reverse(poly[i].p.begin(), poly[i].p.end());
		}
        printf("%.2f\n", PolyUninArea::gao(poly) - eps);
    }
	return 0;
}
