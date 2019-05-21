#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 2010
int sgn(ll x) {
	if (x < 0) {
		return -1;
	} else if (x == 0) {
		return 0;
	} else {
		return 1;
	}
}
struct Point {
	ll x, y;
	Point() {}
	Point(ll x, ll y) : x(x), y(y) {}
	void scan() {
		scanf("%lld%lld", &x, &y); 
	}
	Point operator - (const Point &b) const {
		return Point(x - b.x, y - b.y);
	}
	ll operator ^ (const Point &b) const {
		return x * b.y - y * b.x;
	}
}a[N];

struct Line {
	Point s, e;
	Line() {}
	Line(Point s, Point e) {
		this->s = s;
		this->e = e;
	}
	int relation(Point p) {
		int c = sgn((p - s) ^ (e - s));
		if (c < 0) {
			return 0;
		} else if (c > 0) {
			return 1;
		} else {
			return 2;
		}
	}
}L;
ll Area(Point a1, Point a2, Point a3) {
	return abs(((a2 - a1) ^ (a3 - a2)) + ((a3 - a2) ^ (a1 - a3))); 
}

int main() {
	int n;
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) {
			a[i].scan();
		}
		if (n <= 3) {
			puts("0 0");
			break;
		}
		ll res_max = 0, res_min = 1e9; 
		for (int i = 1; i <= n; ++i) {
			for (int j = i + 1; j <= n; ++j) {
				L = Line(a[i], a[j]);
				ll Max[2] = {0, 0}, Min[2] = {(ll)1e9, (ll)1e9};
				for (int k = 1; k <= n; ++k) {
					if (k == i || k == j) {
						continue;
					}
					int id = L.relation(a[k]);
					Max[id] = max(Max[id], Area(a[i], a[j], a[k]));
					Min[id] = min(Min[id], Area(a[i], a[j], a[k]));
					res_max = max(res_max, (Max[0] + Max[1]) / 2);
					res_min = min(res_min, (Min[0] + Min[1]) / 2);
				}
			}
		}
		printf("%lld %lld\n", res_min, res_max);
	}
	return 0;
}
