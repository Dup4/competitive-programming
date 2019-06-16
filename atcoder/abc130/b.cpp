#include <bits/stdc++.h>
using namespace std;

#define N 110
int n, a[N], x;


int main() {
	while (scanf("%d%d", &n, &x) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
		}
		int res = 1;
		int y = 0;
		for (int i = 1; i <= n; ++i) {
			y += a[i];
			if (y <= x) {
				++res;
			}
		}
		printf("%d\n", res);
	}
	return 0;
}
