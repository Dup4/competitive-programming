#include <bits/stdc++.h>
using namespace std;

int main() {
	int _T; scanf("%d", &_T);
	while (_T--) {
		int n, res = 1e9;
		scanf("%d", &n);
		for (int i = 2; i <= n; ++i) {
			res = min(res, (1 ^ i) + (i ^ n));
		}
		printf("%d\n", 1 ^ n);
	}
	return 0;
}
