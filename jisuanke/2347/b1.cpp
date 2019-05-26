#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n, a[N];

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
		}
		int b[2] = {-1, -1};
		int c[2] = {0, 0};
		for (int i = 1; i <= n; ++i) {
			if (i == n) {
				if (a[i] > b[0] && a[i] > b[1]) {
					if (c[0] < c[1]) {
						++c[0];
					} else {
						++c[1]; 
					}
				} else if (a[i] > b[0]) {
					++c[0];
				} else if (a[i] > b[1]) {
					++c[1];
				}
			} else {
				if (a[i] > b[0]) {
					++c[0];
					b[0] = a[i];
				} else if (a[i] > b[1]) {
					++c[1];
					b[1] = a[i];  
				} else {
					break;
				}
			}
		}
		if (c[0] + c[1] == n) {
			printf("%d\n", abs(c[0] - c[1]));
		} else {
			puts("-1");
		}
	}
	return 0;
}
