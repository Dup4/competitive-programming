#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
int n, x, y, a[N];

bool ok(int l, int r, int x) {
	for (int i = l; i <= r; ++i) {
		if (a[i] < x)
		   return false;	
	}
	return true;
}

void gao() {
	for (int i = 1; i <= n; ++i) {
		if (ok(max(1, i - x), min(n, i + y), a[i])) {
			cout << i << endl;
			return;
		}
	}	
	puts("-1");
}

int main() {
	while (scanf("%d%d%d", &n, &x, &y) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		gao();
	}
	return 0;
}
