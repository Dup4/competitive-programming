#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
int n, x, y, a[N];

bool ok(int x, int l, int r) {
	for (int i = l; i <= r; ++i) if (i != x) {
		if (a[i] <= a[x])
			return 0;
	}
	return 1;
}

void solve() {
	for (int i = 1; i <= n; ++i) {
		int l = max(1, i - x);
		int r = min(n, i + y);
		if (ok(i, l, r)) {
			printf("%d\n", i);
			return;
		}
	}
}

int main() {
	while (scanf("%d%d%d", &n, &x, &y) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		solve();
	}
	return 0;
}
