#include <bits/stdc++.h>
using namespace std;
typedef double db;
const int N = 510;
struct Point {
	db x, y;
	Point () {}
	Point (db x, db y) : x(x), y(y) {}
	void scan() { scanf("%lf%lf", &x, &y); }
	db dis(const Point &p) const { return hypot(x - p.x, y - p.y); }
}arr[N];
int n;
	
void gao() {
	//pd越高, eps越高 炼的越久 pd < 1
	db t = 100, pd = 0.95, eps = 1e-7;
	db res = 1e18;
	Point now = arr[1]; int tmp = 1;
	while (t > eps) {
		for (int i = 1; i <= n; ++i) 
			if (now.dis(arr[tmp]) < now.dis(arr[i])) 
				tmp = i;
		db dis = now.dis(arr[tmp]);
		res = min(res, dis);
		now.x += (arr[tmp].x - now.x) / dis * t;
		now.y += (arr[tmp].y - now.y) / dis * t;
		t *= pd;
	}
	printf("%.2f %.2f %.2f\n", now.x, now.y, res);
}

int main() {
	while (scanf("%d", &n), n) {
		for (int i = 1; i <= n; ++i) arr[i].scan();
		gao();
	}
	return 0;
}
