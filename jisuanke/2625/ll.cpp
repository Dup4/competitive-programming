#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e4 + 10;

int n;
int arr[maxn];

int main() {
	while (~scanf("%d", &n)) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", arr + i);
		}
		if (n == 1) {
			puts("1");
		} else if (n == 2) {
			puts("2");
		} else if (n == 3) {
			puts("6");
		} else if (n == 4) {
			puts("4");
		} else {
			if (n % 4 == 0) {
				puts("4");
			} else if (n % 4 == 1) {
				printf("%d\n", 2 * n);
			} else if (n % 4 == 2) {
				printf("%d\n", n);
			} else if (n % 4 == 3) {
				puts("12");
			}
		}
	}
	return 0;
}
