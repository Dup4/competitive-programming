#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n, a[N], b[N];

bool ok(int *a) {
	if (a[2] + a[n] <= a[1]) return 0;
	if (a[1] + a[n - 1] <= a[n]) return 0;
	for (int i = 2; i < n; ++i) {
		if (a[i - 1] + a[i + 1] <= a[i]) {
			return 0;
		}
	}
	return 1;
}

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		sort(a + 1, a + 1 + n, [](int x, int y) {
			return x > y;		
		});
		b[1] = a[1];
		for (int i = 3; i <= n; ++i) b[i - 1] = a[i];
		b[n] = a[2];
		if (ok(b)) {
			puts("YES");
			for (int i = 1; i <= n; ++i) printf("%d%c", b[i], " \n"[i == n]);
		} else {
			puts("NO");
		}
	}
	return 0;
}
