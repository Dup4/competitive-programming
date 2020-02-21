#include <bits/stdc++.h>
using namespace std;
typedef long long db;
const db eps = 1e-10;
//long long类型时使用
int sgn(db x) { if (x == 0) return 0; return x < 0 ? -1 : 1; }

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

namespace minTriangle {
	struct E { 
		int a, b; double slop;
		bool operator < (const E &other) const {
			return slop < other.slop;
		}
	};
	inline db area(Point a, Point b, Point c) { return abs((b - a) ^ (c - a)); }
	void gao(vector <Point> &p) {
		int n = p.size();
		if (n < 4) {
			puts("0 0");
			return;
		}
		sort(p.begin(), p.end());
		vector <E> vec;
		//rk[i]表示排名为i的点的标号
		//pos[i]表示点i的排名
		vector <int> rk(n), pos(n);
		for (int i = 0; i < n; ++i) {
			for (int j = i + 1; j < n; ++j) {
				vec.push_back({i, j, (p[j].y - p[i].y) * 1.0 / (p[j].x - p[i].x)});
			}
		}
		sort(vec.begin(), vec.end());
		for (int i = 0; i < n; ++i) rk[i] = pos[i] = i;
		db Min = 9e18, Max = 0;
		for (int i = 0; i < (int)vec.size(); ++i) {
			int a = vec[i].a, b = vec[i].b;
			if (pos[a] > pos[b]) swap(a, b);
			if (pos[a] > 0 && pos[b] < n - 1) Max = max(Max, area(p[a], p[b], p[rk[0]]) + area(p[a], p[b], p[rk[n - 1]]));
			if (pos[a] > 0 && pos[b] < n - 1) Min = min(Min, area(p[a], p[b], p[rk[pos[a] - 1]]) + area(p[a], p[b], p[rk[pos[b] + 1]]));
			swap(pos[a], pos[b]); swap(rk[pos[a]], rk[pos[b]]);
		}
		printf("%lld %lld\n", Min, Max);
	}
}

int main() {
	int n; 
	while (scanf("%d", &n) != EOF) {
		vector <Point> p(n);
		for (int i = 0; i < n; ++i) p[i].scan(); 
		minTriangle::gao(p);
	}
	return 0;
}
