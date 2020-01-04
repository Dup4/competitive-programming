#include <bits/stdc++.h>
using namespace std;
using pII = pair<int, int>;
using ll = long long;
using db = double;
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
#define fi first
#define se second
const int N = 3e3 + 10;
const db eps = 1e-8;
int n; pII a[N];
ll f[N]; 

int sgn(db x) {
	if (fabs(x) < eps) return 0;
	if (x < 0) return -1;
	else return 1;
}

struct Point {
	db x, y;
	Point() {}
	Point(db x, db y) : x(x), y(y) {}
	Point operator - (const Point &b) const {
		return Point(x - b.x, y - b.y);
	}
	db operator ^ (const Point &b) const {
		return x * b.y - y * b.x;
	}
	db distance(const Point &p) const {
		return hypot(x - p.x, y - p.y);
	}
};

struct Line {
	Point s, e;
	Line() {}
	Line(Point s, Point e) : s(s), e(e) {}
	int realtion(Point p) {
		int c = sgn((p - s) ^ (e - s));
		if (c < 0) return 1;
		else if (c > 0) return 2;
		else return 3; 
	}
};

struct polygon {
	vector <Point> p;
	polygon() { p.clear(); }
	struct cmp {
		Point po;
		cmp(Point _po) { po = _po; }
		bool operator () (const Point &a, const Point &b) {
			int d = sgn((a - po) ^ (b - po));
			if (d == 0) {
				return sgn(a.distance(po) - b.distance(po)) < 0;
			}
			return d > 0;
		}
	};
	void norm(Point mi) {
		sort(p.begin(), p.end(), cmp(mi));
	}	
};


int main() {
	f[0] = f[1] = 0;
	for (int i = 2; i < N; ++i) {
		f[i] = 1ll * i * (i - 1) / 2;
		f[i] += f[i - 1];
	}
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) 
			scanf("%d%d", &a[i].fi, &a[i].se); 
		ll res = 1ll * (n - 1) * (n - 2) * (n - 3) * (n - 4) / 24; 
		res *= n;
		for (int i = 1; i <= n; ++i) {
			Point P = Point(a[i].fi, a[i].se);
			polygon g = polygon();
			for (int j = 1; j <= n; ++j) if (i != j) {
				g.p.push_back(Point(a[j].fi, a[j].se)); 
			}	
			g.norm(P);
			int nx = 1; 
			for (int j = 0; j < n - 1; ++j) {
				while (1) {
					Line l1 = Line(g.p[j], g.p[nx % (n - 1)]);
					Line l2 = Line(g.p[j], g.p[(nx + 1) % (n - 1)]);
					if (l1.realtion(P) != l2.realtion(P)) { 
						break;
					}
					++nx;
					nx %= (n - 1); 
				}
				if (nx > j) {
					//dbg(nx - j - 1, f[nx - j - 1]);
					res -= f[nx - j - 1];
				} else {
					res -= f[n - 1 - j - 1]; 
				//	dbg(n - 1 - j + nx, f[n - 1 - j + nx]);
				//	res -= f[n - 1 - j + nx];
				}
			}
		}
		printf("%lld\n", res);
	}
	return 0;
}
