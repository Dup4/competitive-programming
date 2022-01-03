#include <bits/stdc++.h>
using namespace std;

#define N 110
int n, a[N];

void solve() {
	int res = 0;
	for (int i = 2; i <= n; ++i) {
		if (a[i] != 1 && a[i - 1] != 1) {
			puts("Infinite");
			return;
		} else if (a[i] == 1) {
			if (a[i - 1] == 2) {
				res += 3;
			} else {
				res += 4;
			}
		} else if (a[i] == 2) {
			res += 3;
			if (i - 2 >= 1 && a[i - 2] == 3) {
				res -= 1;
			}
		} else {
			res += 4;
		}
	}
	puts("Finite");
	printf("%d\n", res);
}

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
		}
		solve();
	}
	return 0;
}
