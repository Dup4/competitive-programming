#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;
const int INF = 0x3f3f3f3f;

struct node {
	int x, y, z;

	node() {}

	node(int x, int y, int z): x(x), y(y), z(z) {}
}a[N];

int n;
int x, y;

bool ok(int h) {
	int l = -INF, r = INF, u = INF, d = -INF;
	for (int i = 1; i <= n; ++i) {
		if (h < a[i].z) return false;
		int x = h - a[i].z;
		l = max(l, a[i].x - x);
		r = min(r, a[i].x + x);
		u = min(u, a[i].y + x);
		d = max(d, a[i].y - x);
	}
	if (l > r || d > u) return false;
	x = l, y = d;
	return true;
}

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d %d %d", &a[i].x, &a[i].y, &a[i].z);
		}
		int l = 0, r = INF, res = INF;
		x = INF, y = INF;
		while (r - l >= 0) {
			int mid = (l + r) >> 1;
			if (ok(mid)) {
				r = mid -1;
				res = mid;
			} else {
				l = mid + 1;
			}
		}
		ok(res);
		printf("%d %d %d\n", x, y, res);
	}
	return 0;
}
