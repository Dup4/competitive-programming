#include <bits/stdc++.h>
using namespace std;
using db = double;

struct Point {
	db x, y;
	Point() {}
	Point(db x, db y) : x(x), y(y) {}
	void input() { cin >> x >> y; }
}A, B, C;

Point waixin(Point a, Point b, Point c) {
    double a1 = b.x - a.x, b1 = b.y - a.y, c1 = (a1 * a1 + b1 * b1) / 2;
    double a2 = c.x - a.x, b2 = c.y - a.y, c2 = (a2 * a2 + b2 * b2) / 2;
    double d = a1 * b2 - a2 * b1;
    return Point(a.x + (c1 * b2 - c2 * b1) / d, a.y + (a1 * c2 -a2 * c1) / d);
}

int main() {
	A.input(); B.input(); C.input();
	Point D = waixin(A, B, C);
	printf("%.3f %.3f\n", D.x, D.y);
	return 0;
}
