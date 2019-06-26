#include <bits/stdc++.h>
using namespace std;

#define N 110
int n, k, a[N];

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &k);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
		}
		sort(a + 1, a + 1 + n);
		int mid = a[1] + k;
		if (abs(a[1] - mid) <= k && abs(a[n] - mid) <= k) {
			printf("%d\n", mid);
		} else {
			puts("-1");
		}
	}
	return 0;
}
