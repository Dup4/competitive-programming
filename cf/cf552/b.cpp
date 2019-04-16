#include <bits/stdc++.h>
using namespace std;

#define N 110
int n, a[N];

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
		}
		sort(a + 1, a + 1 + n);
		n = unique(a + 1, a + 1 + n) - a - 1;
		if (n == 1) {
			puts("0");
		} else if (n == 2) {
			if ((a[2] - a[1]) % 2 == 0) {
				printf("%d\n", (a[2] - a[1]) / 2);
			} else {
				printf("%d\n", a[2] - a[1]);
			}
		} else if (n == 3) {
			int x = a[3] - a[2], y = a[2] - a[1];
			if (x == y) {
				printf("%d\n", x);
			} else {
				puts("-1");
			}
		} else {
			puts("-1");
		}
	}
	return 0;
}
