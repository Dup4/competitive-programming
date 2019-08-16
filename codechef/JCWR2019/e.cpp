#include <bits/stdc++.h>
using namespace std;

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		int n; scanf("%d", &n);
		if (n >= 7) {
			puts("1.000000");
		} else {
			int x = 0;
			for (int i = 0; i < 7; ++i) {
				for (int j = i, k = 0; k < n; ++j, ++k) {
					if (j % 7 >= 2 && j % 7 <= 4) {
						++x;
						break;
					}
				}
			}
			printf("%.6f\n", x * 1.0 / 7);
		}
	}
	return 0;
}
