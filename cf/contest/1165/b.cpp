#include <bits/stdc++.h>
using namespace std;

#define N 200010
int n, a[N];

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
		}
		sort(a + 1, a + 1 + n);
		int res = 0;
		int now = 1;
		for (int i = 1; i <= n; ++i) {
			if (a[i] >= now) {
				++res;
				++now;
			}
		}
		printf("%d\n", res);
	}
	return 0;
}
