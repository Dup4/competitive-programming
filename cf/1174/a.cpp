#include <bits/stdc++.h>
using namespace std;

#define N 2010
int n, a[N];

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n * 2; ++i) {
			scanf("%d", a + i);
		}
		sort(a + 1, a + 1 + n * 2);
		int l = 0, r = 0;
		for (int i = 1; i <= n; ++i) {
			l += a[i];
		}
		for (int i = n + 1; i <= n * 2; ++i) {
			r += a[i];
		}
		if (l == r) {
			puts("-1");
		} else {
			for (int i = 1; i <= 2 * n; ++i) {
				printf("%d%c", a[i], " \n"[i == 2 * n]);
			}
		}
	}
	return 0;
}
