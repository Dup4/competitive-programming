#include <bits/stdc++.h>
using namespace std;

using db = double; 
const int maxn = 300;
const db eps = 1e-8;
int sgn(db x) {
	if (fabs(x) < eps) return 0;
	if (x < 0) return -1;
	return 1;
}
struct Point { 
	db x, y;
    Point(db _x = 0, db _y = 0) {
        x = _x; y = _y;
    }
    Point operator - (const Point& p1) const {
        return Point(x - p1.x,y - p1.y);
    }
    Point operator + (const Point& p1)const {
        return Point(x + p1.x,y + p1.y);
    }
    bool operator < (const Point &b) const {
	   return sgn(x - b.x) == 0 ? sgn(y - b.y) < 0 : x < b.x;	
    }
    bool operator == (const Point& b) const {
		return sgn(x - b.x) == 0 && sgn(y - b.y) == 0;
    }
    db operator ^ (const Point &b) const {
		return x * b.y - y * b.x;
	}
    db operator * (const Point& b) const {
		return x * b.x + y * b.y;
    }
    Point operator * (const db &k) const {
		return Point(x * k, y * k);
	}
};
Point LineCross(const Point &a,const Point &b,const Point &c,const Point &d){
    db u = (b - a) ^ (c - a),v = (a - b) ^ (d - b);
    return Point((c.x * v + d.x * u) / (u + v),(c.y * v + d.y * u) / (u + v));
}
//计算多边形面积
db PolygonArea(Point p[], int n) {
    if(n < 3) return 0.0;
    db s = p[0].y * (p[n - 1].x - p[1].x);
    p[n] = p[0];
    for(int i = 1; i < n; ++ i) 
        s += p[i].y * (p[i - 1].x - p[i + 1].x);
    return fabs(s * 0.5);
}
//ConvexPolygonIntersectArea 
db CPIA(Point a[], Point b[], int na, int nb) {
    Point p[20], tmp[20];
    int tn, sflag, eflag;
    a[na] = a[0], b[nb] = b[0];
    memcpy(p, b ,sizeof(Point) * (nb + 1));
    for(int i = 0; i < na && nb > 2; i++) {
        sflag = sgn((a[i + 1] - a[i]) ^ (p[0] - a[i]));
        for(int j = tn = 0; j < nb; j++, sflag = eflag) {
            if(sflag>=0) tmp[tn++] = p[j];
            eflag = sgn((a[i + 1] - a[i]) ^ (p[j + 1] - a[i]));
            if((sflag ^ eflag) == -2)
                tmp[tn++] = LineCross(a[i], a[i + 1], p[j], p[j + 1]); ///求交点
        }
        memcpy(p, tmp, sizeof(Point) * tn);
        nb = tn, p[nb] = p[0];
    }
    if(nb < 3) return 0.0;
    return PolygonArea(p, nb);
}
//SimplePolygonIntersectArea 调用此函数 {
db SPIA(Point a[], Point b[], int na, int nb) {
    int i, j;
    Point t1[4], t2[4];
    float res = 0, num1, num2;
    a[na] = t1[0] = a[0], b[nb] = t2[0] = b[0];
    for(i = 2; i < na; i++) {
        t1[1] = a[i-1], t1[2] = a[i];
        num1 = sgn((t1[1] - t1[0]) ^ (t1[2] - t1[0]));
        if(num1 < 0) swap(t1[1], t1[2]);
        for(j = 2; j < nb; j++) {
            t2[1] = b[j - 1], t2[2] = b[j];
            num2 = sgn((t2[1] - t2[0]) ^ (t2[2] - t2[0]));
            if(num2 < 0) swap(t2[1], t2[2]);
            res += CPIA(t1, t2, 3, 3) * num1 * num2;
        }
    }
    return res;
}
Point a[50],b[50];
   
int main() {
	cout << fixed << setprecision(8);
    db x1,x2,x3,x4,y1,y2,y3,y4;
	while (cin >> x1 >> y1 >> x2 >> y2) {
		cin >> x3 >> y3 >> x4 >> y4;
      	a[0] = Point(x1,y1);
      	a[2] = Point(x2,y1);
      	a[1] = Point(x1,y2);
      	b[0] = Point(x3,y3);
      	b[1] = Point(x3,y4);
      	b[2] = Point(x4,y4);
      	b[3] = Point(x4,y3);
		cout << fabs(SPIA(a, b, 3, 4)) << endl;
	}
	return 0;
}
