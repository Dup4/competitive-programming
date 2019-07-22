#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n;

void P(int x, int y) {
	printf("%d %d\n", x, y);
}

int main() {
	while (scanf("%d", &n) != EOF) {
		int m = 1;
		while (m < n) m <<= 1;
		if (n < 3 || m == n) puts("No");
		else {
			puts("Yes");
			P(1, n + 2); P(n + 2, 3);
			P(3, n + 1); P(n + 1, 2);
			P(2, n + 3);
			for (int i = 4; i < n; i += 2) {
				P(i, n + 1); P(i, n + i + 1);
				P(i + 1, n + 1); P(n + i, i + 1);
			}
			if (n % 2 == 0) {
				for (int i = 2; i < n; ++i) {
					if ((n ^ (i ^ 1)) < n) {
						int a = i;
						int b = n ^ i ^ 1;
						P(n, a); P(n + n, b);
						break;
					}
				}
			}
		}
	}
	return 0;
}
