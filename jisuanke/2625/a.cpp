#include <bits/stdc++.h>
using namespace std;

#define N 1100
int n, T, a[N];

int main() {
	while (scanf("%d%d", &n, &T) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
		}
		sort(a + 1, a + 1 + n);
		int res = 0;
		for (int i = 1; i <= n; ++i) {
			if (a[i] <= T) {
				T -= a[i];
				++res;
			} else {
				break;
			}
		}
		printf("%d\n", res);
	}
	return 0;
}
