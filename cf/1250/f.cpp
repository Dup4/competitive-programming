#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;
	while (scanf("%d", &n) != EOF) {
		int res = 1e9;
		for (int i = 1; i <= n; ++i) {
			if (n % i == 0) {
				res = min(res, i + n / i);
			}
		}
		res *= 2;
		printf("%d\n", res);
	}
	return 0;
}
