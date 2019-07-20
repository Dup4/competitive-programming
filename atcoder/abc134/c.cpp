#include <bits/stdc++.h>
using namespace std;

#define N 200010
int n, a[N], c[N], d[N];

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
		}
		c[0] = 0;
		c[1] = a[1];
		for (int i = 2; i <= n; ++i) {
			c[i] = max(c[i - 1], a[i]);
		}
		d[n + 1] = 0;
		d[n] = a[n];
		for (int i = n - 1; i >= 1; --i) {
			d[i] = max(d[i + 1], a[i]);
		}
		for (int i = 1; i <= n; ++i) {
			printf("%d\n", max(c[i - 1], d[i + 1]));
		}
	}
	return 0;
}
