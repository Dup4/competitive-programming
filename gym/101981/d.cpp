#include <bits/stdc++.h>
using namespace std;

#define db double
#define N 110
const db eps = 1e-7;
int n;
struct node {
	db x, y, z;
	node() {
		x = y = z = 0;
	}
	void scan() {
		scanf("%lf%lf%lf", &x, &y, &z);
	}
}a[N];
db dis(node a, node b) {
	return sqrt(1.0 * (a.x - b.x) * (a.x - b.x) + 1.0 * (a.y - b.y) * (a.y - b.y) + 1.0 * (a.z - b.z) * (a.z - b.z));
}

db solve() {
	db step = 100000, ans = 1e30, mt;
	node c = node();
	int s = 1;
	while (step > eps) {
		for (int i = 1; i <= n; ++i) {
			if (dis(c, a[s]) < dis(c, a[i])) {
				s = i;
			}
		}
		mt = dis(c, a[s]);
		ans = min(ans, mt);
		c.x += (a[s].x - c.x) / mt * step;
		c.y += (a[s].y - c.y) / mt * step;
		c.z += (a[s].z - c.z) / mt * step;
		step *= 0.98;
	}
	return ans;
}

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) {
			a[i].scan();
		}
		printf("%.16f\n", solve());
	}
	return 0;
}
