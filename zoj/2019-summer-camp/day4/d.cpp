#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define db double
#define N 1000010
int n, r[N], d[N]; 
db f[N]; 

const db PI = acos(-1.0);
const db eps = 1e-8;
int sgn(db x) {
	if (fabs(x) < eps) return 0;
	if (x < 0) return -1;
	else return 1;
}
struct Point {
	db x, y;
	Point() {}
	Point (db x, db y) : x(x), y(y) {}
	db len() {
		return hypot(x, y);
	}
	db len2() {
		return x * x + y * y;
	}
	Point operator + (const Point &b) const {
		return Point(x + b.x, y + b.y);
	}
	Point operator - (const Point &b) const {
		return Point(x - b.x, y - b.y);
	}
	db operator ^ (const Point &b) const {
		return x * b.y - y * b.x;
	}
	db operator * (const Point &b) const {
		return x * b.x + y * b.y;
	}
	Point operator * (const db &k) const {
		return Point(x * k, y * k);
	}
	Point operator / (const db &k) const {
		return Point(x / k, y / k);
	}
	db distance(Point p) {
		return hypot(x - p.x, y - p.y);
	}
	Point trunc(db r) {
		db l = len();
		if (!sgn(l)) return *this;
		r /= l;
		return Point(x * r, y * r);
	}
	Point rotleft() {
		return Point(-y, x);
	}
	Point rotright() {
		return Point(y, -x);
	}
	db rad(Point a, Point b) {
		Point p = *this;
		return fabs(atan2(fabs((a - p) ^ (b - p)), (a - p) * (b - p)));
	}

};

struct Line {
	Point s, e;
	Line() {}
	Line(Point s, Point e) : s(s), e(e) {}
    db length() {
		return s.distance(e);
	}	
	db dispointtoline(Point p) {
		return fabs((p - s) ^ (e - s)) / length(); 
	}
	Point lineprog(Point p) {
		return s + (((e - s) * ((e - s) * (p - s))) / ((e - s).len2()));
	}
};

struct circle {
	Point p;
	db r;
	circle() {}
	circle(db x, db y, db r) {
		p = Point(x, y);
		this->r = r;
	}
	int relation(Point b) {
		db dst = b.distance(p);
		if (sgn(dst - r) < 0) return 2;
		else if (sgn(dst - r) == 0) return 1;
		return 0;
	}
	int relationline(Line v) {
		db dst = v.dispointtoline(p);
		if (sgn(dst - r) < 0) return 2;
		else if (sgn(dst - r) == 0) return 1;
		return 0;
	}
	int pointcrossline(Line v, Point &p1, Point &p2) {
		if ((*this).relationline(v) == 0) return 0;
		Point a = v.lineprog(p);
		db d = v.dispointtoline(p);
		d = sqrt(r * r - d * d);
		if (sgn(d) == 0) {
			p1 = a;
			p2 = a;
			return 1;
		}
		p1 = a + (v.e - v.s).trunc(d);
		p2 = a - (v.e - v.s).trunc(d);
		return 2; 
	}
	int tangentline(Point q, Line &u, Line &v) {
		int x = relation(q);
		if (x == 2) return 0;
		if (x == 1) {
			u = Line(q, q + (q - p).rotleft());
			v = u;
			return 1;
		}
		db d = p.distance(q);
		db l = r * r / d;
		db h = sqrt(r * r - l * l);
		u = Line(q, p + ((q - p).trunc(l) + (q - p).rotleft().trunc(h)));
		v = Line(q, p + ((q - p).trunc(l) + (q - p).rotright().trunc(h)));
		return 2;
	}
}a[N];  

int main() {
	while (scanf("%d", &n) != EOF) {
		ll sum = 0;
		for (int i = 1; i <= n; ++i) {
			scanf("%d", r + i);  
			sum += r[i]; 
		}
		d[1] = 0;
		for (int i = 2; i <= n; ++i) {
			scanf("%d", d + i);
		}
		for (int i = 1; i <= n; ++i) {
			a[i] = circle(d[i], 0, r[i]);   
		}
		f[1] = 1;
		db res = 0;
		for (int i = 2; i <= n; ++i) {
			Line up[2], down[2];
			Point U[2], D[2];
			a[i - 1].tangentline(Point(d[i], r[i]), up[0], up[1]);
			a[i - 1].tangentline(Point(d[i], -r[i]), down[0], down[1]);
		//	cout << up[0].e.x << " " << up[0].e.y << endl;
		//	cout << up[1].e.x << " " << up[1].e.y << endl;
		//	cout << down[0].e.x << " " << down[1].e.x << endl;
		//	cout << down[1].e.x << " " << down[1].e.y << endl;
		//	a[i - 1].pointcrossline(up[0], U[0], U[1]);
		//	a[i - 1].pointcrossline(down[1], D[0], D[1]);	
			db angle = Point(d[i - 1], 0).rad(up[1].e, down[1].e); 
			f[i] = f[i - 1] * (angle / (2 * PI));
//		    res += f[i - 1] * ((2 * PI - angle) / (2 * PI)) * (i - 2);	
		}
//		res += f[n] * (n - 1); 
		for (int i = 2; i < n; ++i) res += (i - 1) * f[i];
		printf("%.16f\n", res);
	}
	return 0;
}
