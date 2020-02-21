#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 10;
int n;

struct Point {
    ll x, y;
    Point() {}
    Point(ll _x, ll _y) {
        x = _x, y = _y;
    }
	bool operator != (const Point &other) const {
		return x != other.x || y != other.y;
	}
    Point operator+(const Point &other) const {
        return {x + other.x, y + other.y};
    }
}a[N];

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%lld%lld", &a[i].x, &a[i].y);
		if (n & 1) puts("NO");
		else {
			Point p = a[n / 2 + 1] + a[1];
			for (int i = 1, j = n / 2 + 1; i <= n / 2; ++i, ++j) {
				if (a[j] + a[i] != p) {
					puts("NO");
					return 0;
				}
			}
			puts("YES");
		}
	}
	return 0;
}
