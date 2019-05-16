#include <bits/stdc++.h>
using namespace std;

int n, x;

int main() {
	while (scanf("%d", &n) != EOF) {
		int res = 1e9;
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &x);
			res = min(res, x / max(i - 1, n - i));
		}
		printf("%d\n", res);
	}
	return 0;
}
