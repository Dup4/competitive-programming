#include <bits/stdc++.h>
using namespace std;

#define N 200010 
int n, a[N];

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
		}
		if (n == 1) {
			puts("0");
			continue;
		}
		int res = 0; 
		int dir = 1;   
		// 0 up
		// 1 down	
		for (int i = 2; i <= n; ++i) {
			if (dir == 1) { //下降
				if (a[i] >= a[i - 1]) {
					dir = 0;
					++res;
				}
			} else {
				if (a[i] <= a[i - 1]) {
					dir = 1;
				}
			}
		}
		printf("%d\n", res);
	}
	return 0;
}
