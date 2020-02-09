#include <bits/stdc++.h>
using namespace std;
const int N = 4e6 + 10;
int n, x[N], y[N];

const double eps = 1e-8;

int sgn(double x) {
    if (fabs(x) < eps) return 0;
    else return x > 0 ? 1 : -1;
}

struct Point {
    double x, y;

    Point() {}

    Point(double _x, double _y) {
        x = _x, y = _y;
    }

    void input() {
        scanf("%lf %lf", &x, &y);
    }

    double distance(const Point &other) const {
        return hypot(x - other.x, y - other.y);
    }

    bool operator<(const Point &other) const {
        if (sgn(x - other.x) == 0) {
            return y < other.y;
        } else {
            return x < other.x;
        }
    }

    double operator^(const Point &other) const {
        return x * other.y - y * other.x;
    }

    Point operator+(const Point &other) const {
        return {x + other.x, y + other.y};
    }

    Point operator-(const Point &other) const {
        return {x - other.x, y - other.y};
    }
} p[N], q[N], sta[N];

void convehull(Point *s, int &n) {
    sort(s, s + n);
    int top = 0;
    s[n] = s[0];
    for (int i = 0; i < n; ++i) {
        while (top > 1 && sgn((sta[top - 1] - sta[top - 2]) ^ (s[i] - sta[top - 2])) <= 0) {
            --top;
        }
        sta[top++] = s[i];
    }
    int k = top;
    for (int i = n - 2; i >= 0; --i) {
        while (top > k && sgn((sta[top - 1] - sta[top - 2]) ^ (s[i] - sta[top - 2])) <= 0) {
            top--;
        }
        sta[top++] = s[i];
    }
    if (n > 1) top--;
    n = top;
    for (int i = 0; i < n; ++i) {
        s[i] = sta[i];
    }
}

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%d%d", x + i, y + i);
		if (n >= 2000) puts("NO");
		else {
			int cnt = 0;
			for (int i = 1; i <= n; ++i) {
				for (int j = 1; j <= n; ++j) if (i != j) {
					p[cnt++] = Point(x[i] - x[j], y[i] - y[j]);
				}
			}
			convehull(p, cnt);
			for (int i = 0; i < n; ++i) q[i] = Point(x[i + 1], y[i + 1]);
			convehull(q, n);
			if (cnt == n) puts("YES");
			else puts("NO");
		}
	}
	return 0;
}
