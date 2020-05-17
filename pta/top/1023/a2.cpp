#include <bits/stdc++.h>
using namespace std;
using db = double;
#define SZ(x) (int(x.size()))
const int N = 610;
const db eps = 1e-10;
int sgn(db x) { if (fabs(x) < eps) return 0; return x < 0 ? -1 : 1; }
int n, m;

struct Point {
	db x, y; int id;
	Point(db x = 0, db y = 0, int id = 0) : x(x), y(y), id(id) {}
	void scan() { scanf("%lf%lf", &x, &y); }
	void output() { printf("%lf %lf\n", x, y); }
	db dis2(Point b) { return (x - b.x) * (x - b.x) + (y - b.y) * (y - b.y); }
	Point operator - (const Point &b) const { return Point(x - b.x, y - b.y); }
	db operator ^ (const Point &b) const { return x * b.y - y * b.x; }
	bool operator < (const Point &b) const { return sgn(x - b.x) == 0 ? sgn(y - b.y) < 0 : x < b.x; }
}p[N];

struct Polygon {
	vector <Point> p;
	Polygon() { p.clear(); }
	Polygon(int n) { p.clear(); p.resize(n); }
	int sze() { return p.size(); }
	Point& operator[](int x) { return p[(x + sze()) % sze()]; }
	void add(Point q) { p.push_back(q); }
	void scan(int n = -1) { if (n == -1) scanf("%d", &n); (*this) = Polygon(n); for (int i = 0; i < n; ++i) { p[i].scan(); p[i].id = i; } }
	void output() { for (int i = 0; i < SZ(p); ++i) p[i].output(); }
	struct cmpNorm {
		Point p;
		cmpNorm(Point p) : p(p) {}
		bool operator () (Point a, Point b) {
			int d = sgn((a - p) ^ (b - p));
			if (d == 0) {
				return sgn(a.dis2(p) - b.dis2(p) < 0);
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
	db getArea() {
		if (p.empty()) return -1;
		norm();
		db res = 0;
		for (int i = 0; i < sze(); ++i) {
			int j = (i + 1) % sze();
			res += (p[i] ^ p[j]);
		}
		return fabs(res / 2);
	}
};

db g[N][15];
int pre[N][15];
int f[N][15];

int main() {
	scanf("%d%d", &n, &m);
	Polygon po; po.scan(n);
	po.norm();
	Polygon res = Polygon();
	db area = 0;
	int pos = -1;
	for (int i = 0; i < n; ++i) {
		for (int j = 1; j <= m; ++j) {
			pre[i][j] = -1;
			g[i][j] = 0;
			f[i][j] = -1;
		}
		f[i][1] = 1;
		for (int j = i + 1; j < i + n; ++j) {
			for (int k = 1; k <= m; ++k) {
				pre[j][k] = -1;
				g[j][k] = 0;
				f[j][k] = -1;
			}
			db tmp = po[j] ^ po[i];
			for (int k = i; k < j; ++k) {
				for (int o = 1; o < m; ++o) if (f[k][o] != -1) {
					db ar = g[k][o] + (po[j] ^ po[k]);
					if (f[j][o + 1] == -1 || (f[j][o + 1] == 1 && fabs(ar + tmp) > fabs(g[j][o + 1] + tmp))) {
						g[j][o + 1] = ar;
						pre[j][o + 1] = k;
						f[j][o + 1] = 1;
					}
				}
			}
			if (f[j][m] == 1) {
				vector <int> vec;
				int pos = j;
				for (int j = m; j >= 1; --j) {
					
				}
				db now = fabs(g[j][m] + tmp);
				if (now > area) {
					area = now;
					pos = j;
				}
			}
		}
	}
	cout << area << endl;
//	res.output();
	vector <int> vec;
	for (int i = m; i >= 1; --i) {
		cout << pos << endl;
		vec.push_back(po[pos].id);
		pos = pre[pos][i];
	}
	sort(vec.begin(), vec.end(), [&](int x, int y) { return x > y; });
	for (int i = 0; i < m; ++i)
		printf("%d%c", vec[i], " \n"[i == m - 1]);
	return 0;
}
