#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, m, r;
	while (scanf("%d%d%d", &n, &m, &r) != EOF) {
		int Max = -1, Min = 1e9;
		for (int i = 1, x; i <= n; ++i) {
			scanf("%d", &x);
			Min = min(Min, x);
		}
		for (int i = 1, x; i <= m; ++i) {
			scanf("%d", &x);
			Max = max(Max, x);
		}
		printf("%d\n", max(r, (r / Min) * Max + r % Min));
	}
	return 0;
}
