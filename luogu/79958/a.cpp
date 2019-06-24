#include <bits/stdc++.h>
using namespace std;

#define N 10010
int n, a[N];

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
		}
		int res = 0;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j < i; ++j) if (a[i] < a[j]) {
				++res;
			}
		}
		printf("%d\n", res);
	}
	return 0;
}
