#include <bits/stdc++.h>
using namespace std;

#define N 110
int n, v[N], a, b, c, d;

int main() {
	while (scanf("%d%d%d%d%d", &n, &a, &b, &c, &d) != EOF) {
		int sum = 0;
		for (int i = 1; i <= n; ++i) {
			scanf("%d", v + i);
			sum += v[i];
		}
		int ans[2] = {sum, sum};
		if (sum >= a) {
			ans[0] -= b;
		}	
		if (sum >= c) {
			ans[1] -= d;
		}
		printf("%d\n", min(ans[0], ans[1]));
	}
	return 0;
}
