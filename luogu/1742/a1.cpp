#include <bits/stdc++.h>
using namespace std;
using db = double;
const int N = 1e5 + 10;
const db eps = 1e-10;
mt19937 rnd(time(0));
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
	//顺时针旋转90度
	Point rotright() { return Point(y, -x); }
}p[N];


struct Circle {
	Point p; db r;
	Circle() {}
	Circle(Point p, db r) : p(p), r(r) {}
	Circle(db x, db y, db r) : p(Point(x, y)), r(r) {}
	//三角形的相关圆
	//外接圆 opt = 0 可处理三点共线的情况 
	Circle(Point a, Point b, Point c, int opt = 0) {
		if (opt == 0) {
			Point p0 = (a + b) / 2;
			Point v0 = (b - a).rotright();
			Point p1 = (a + c) / 2;
			Point v1 = (c - a).rotright();
			db t = ((p1 - p0) ^ v1) / (v0 ^ v1);
			p = p0 + v0 * t;
			r = p.dis(a);
		} 
	}	
};

int main() {
	int n; 
	while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; ++i) p[i].scan();
		shuffle(p + 1, p + 1 + n, rnd);
		Circle cir(0, 0, 0);
		//cir.r 存的是半径的平方
        for (int i = 1; i <= n; ++i) {
            //p_i不在前i - 1个点的最小覆盖圆上
            if (sgn((cir.p - p[i]).len2() - cir.r) > 0) {
				cir.p = p[i];
				cir.r = 0;
                for (int j = 1; j < i; ++j) {
                    if (sgn((cir.p - p[j]).len2() - cir.r) > 0) {
						cir.p = (p[i] + p[j]) / 2;
						cir.r = (p[j] - cir.p).len2();
                        for (int k = 1; k < j; ++k) {
                            if (sgn((cir.p - p[k]).len2() - cir.r) > 0) {
                                cir = Circle(p[i], p[j], p[k]);
                                cir.r = (p[k] - cir.p).len2();
                            }
                        }
                    }
                }
            }
        }
        printf("%.10f\n", sqrt(cir.r));
        printf("%.10f %.10f\n", cir.p.x, cir.p.y);
    }
    return 0;
}
