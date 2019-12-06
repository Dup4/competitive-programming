#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int n, a[N];

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
		}
		sort(a + 1, a + 1 + n, [&](int x, int y) { return x > y; });
		int res = 0;
		for (int i = 1; i <= n; ++i) {
			if (a[i] > i) {
				res = i;
			}
		}
		printf("%d\n", res);
	}
	return 0;
}
