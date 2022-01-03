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
	cout << l << " " << r << " " << d << " " << u << endl;;
	x = l;
	y = d;
	cout << x << " " << y << endl;
	return true;
}

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d %d %d", &a[i].x, &a[i].y, &a[i].z);
		}
		int l = 0, r = INF, res = 5;
		x = -INF, y = -INF;
		int tmp = ok(res);
		cout << x << " " << y << endl;
		printf("%d %d %d\n", x, y, res);
	}
	return 0;
}
