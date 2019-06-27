#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n, a[N];

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
		}
		sort(a + 1, a + 1 + n);
		int res = a[n];
		for (int i = n - 1; i >= 1; --i) {
			if (a[n] % a[i] != 0) {
				res += a[i];
				break;
			}
		}
		printf("%d\n", res);
	}
	return 0;
}
