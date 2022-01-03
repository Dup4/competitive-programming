#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
int n, a[N], x;

int main() {
	while (scanf("%d%d", &n, &x) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		sort(a + 1, a + 1 + n);
		int res = 1;
		for (int i = 2; i <= n; ++i) {
			if (a[i] + a[i - 1] <= x) {
				++res;
			} else break;
		}
		printf("%d\n", res);
	}
	return 0;
}
