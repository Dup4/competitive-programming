#include <bits/stdc++.h>
using namespace std;

#define N 110
int n, a[N];

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		int res = 0;
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
		}
		res = 3 * a[1];
		for (int i = 2; i <= n; ++i) {
			res = max(res, a[i] + 1);
		}
		if (res & 1) ++res;
		printf("%d\n", res);
	}
	return 0;
}
