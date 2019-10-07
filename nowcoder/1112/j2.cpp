/*
 * 多边形的交，多边形的边一定是要按逆时针方向给出
 * 还要判断是凸包还是凹包，调用相应的函数
 * 面积并，只要和面积减去交即可
 */
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
    //return PolygonArea(a, na) + PolygonArea(b, nb)-res; //面积并
}
Point p1[maxn], p2[maxn];
int n1, n2; db x[4], y[4];
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(8);
	while (cin >> x[0] >> y[0] >> x[1] >> y[1]) {
		cin >> x[2] >> y[2] >> x[3] >> y[3];
		n1 = 3, n2 = 4;
		p1[0].x = x[0], p1[0].y = y[0];
		p1[1].x = x[0], p1[1].y = y[1];
		p1[2].x = x[1], p1[2].y = y[0];
		p2[0].x = x[2], p2[0].y = y[2];
		p2[1].x = x[2], p2[1].y = y[3];
		p2[2].x = x[3], p2[2].y = y[3];
		p2[3].x = x[3], p2[3].y = y[2];
		cout << fabs(SPIA(p1, p2, 3, 4)) << endl;
	}
    return 0;
}
