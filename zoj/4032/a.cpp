#include <bits/stdc++.h>
using namespace std;

#define N 1010

int main() {
	int T; cin >> T;
	while (T--) {
		int n; scanf("%d", &n);
		if (n == 2) {
			puts("0 2 1 3");
		} else {
			for (int i = 0; i < n - 1; ++i) {
				printf("%d %d ", i, n + i);
			}
			printf("%d %d\n", n - 1, 3 * n - 2);
		}
	}
	return 0;
}
