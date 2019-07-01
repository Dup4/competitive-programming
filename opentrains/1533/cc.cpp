#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 2010
int n, m, p; 
struct node {
	int x, y;
	node() {}
	void scan() {
		scanf("%d%d", &x, &y);
		x = n - x + 1;
		if (y <= m) {
			y = m - y + 1;
		} else {
			y -= m;
		}
	}
	bool operator < (const node &other) const {
		if (x + y != other.x + other.y) {
			return x + y > other.x + other.y;
		} else {
			return y > other.y;
		}
	}
}a[N];

int main() {
	while (scanf("%d%d%d", &n, &m, &p) != EOF) {
		for (int i = 1; i <= p; ++i) {
			a[i].scan();
		}
		sort(a + 1, a + 1 + p);
		ll base = 0, res = 0;
		for (int i = 1; i <= p; ++i) {
			res = max(res, base + a[i].x + a[i].y);
			++base;
		}
		printf("%lld\n", res);
	}
	return 0;
}
