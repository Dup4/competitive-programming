#include <bits/stdc++.h>

using namespace std;

const double eps = 1e-8;
const double PI = acos(-1.0);

int sgn(double x) {
	if (fabs(x) < eps) return 0;
	else return x > 0 ? 1 : -1;	
}

struct Point {
	double x, y;
	Point() {}
	Point(double _x, double _y) {
		x = _x;
		y = _y;
	}

	double distance(Point p) {
		return hypot(x - p.x, y - p.y);
	}

	Point operator - (const Point &b) const {
		return Point(x - b.x, y - b.y);
	}

	double operator ^ (const Point &b) const {
		return x * b.y - y * b.x;
	}

	double operator * (const Point &b) const {
		return x * b.x + y * b.y;
	}
};

struct Line {
	Point s, e;
	Line() {}
	Line(Point _s, Point _e) {
		s = _s;
		e = _e;
	}

	double length() {
		return s.distance(e);
	}

	double dispointtoline(Point p) {
		return fabs((p - s) ^ (e - s)) / length();
	}

	double dispointtoseg(Point p) {
		if (sgn((p - s) * (e - s) ) < 0 || sgn((p - e) * (s - e)) < 0) {
			return min(p.distance(s), p.distance(e));
		} else {
			return dispointtoline(p);
		}
	}
};

double rx, ry, r, x, y;

double solve(Point p) {
	Point p1 = Point(x, y);
	Line l = Line(p1, p);
	Point o = Point(rx, ry);
	double dis = l.dispointtoseg(o);
	if (sgn(dis - r) >= 0) {
		return p1.distance(p);
	} else {
		double a = p1.distance(o);
		double b = r;
		double c = p1.distance(p);
		double arc1 = (a * a + b * b - c * c) / (2.0 * a * b);
		arc1 = acos(arc1);
		double arc2 = acos(r / a);
		double arc3 = arc1 - arc2;
		double d = sqrt(a * a - r * r);
		return d + r * arc3;
	}
}

int main() {
	int t;
	scanf("%d" ,&t);
	while (t--) {
		scanf("%lf %lf %lf %lf %lf", &rx, &ry, &r, &x, &y);
		double ans = solve(Point(rx + r, ry));
		ans = min(ans, solve(Point(rx - r, ry)));
		printf("%.4f\n", ans + r * PI / 2);
	}
	return 0;
}
