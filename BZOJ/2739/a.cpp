#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 10;
int n, ans[N];

struct Point {
	ll x, y; int id;
	ll dis(const Point &b) { return (x - b.x) * (x - b.x) + (y - b.y) * (y - b.y); }
}a[N];

bool check(int id, int i, int j) {
	if (i < id || i > n + id) return 0;
	if (j < id || j > n + id) return 1;
	ll dis1 = a[id].dis(a[i]);
	ll dis2 = a[id].dis(a[j]);
	if (dis1 == dis2) return a[i].id < a[j].id;
	return dis1 > dis2;
}

void gao(int l, int r, int L, int R) {
	if (l > r) return;
	int mid = (l + r) >> 1;
	int pos = 0; 
	for (int i = L; i <= R; ++i) {
		if (check(mid, i, pos))
			pos = i;
	}
	ans[mid] = pos > n ? pos - n : pos;
	gao(l, mid - 1, L, pos);
	gao(mid + 1, r, pos, R);
}

int main() {
	int _T; scanf("%d", &_T);
	while (_T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			scanf("%lld%lld", &a[i].x, &a[i].y);
			a[i].id = i;
			a[i + n] = a[i];
		}
		gao(1, n, 1, n << 1);
		for (int i = 1; i <= n; ++i)
			printf("%d\n", ans[i]);
	}
	return 0;
}
