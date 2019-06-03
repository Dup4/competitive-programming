#include <bits/stdc++.h>
using namespace std;

#define N 110
int n, a[N];
int f[N], base; 

int solve(int id) {
	int Max = 0;
	for (int i = 1; i <= n; ++i) if (i != id) {
		f[i] = 1;	
		for (int j = 1; j < i; ++j) if (j != id) {
			if (a[i] > a[j]) {
				f[i] = max(f[i], f[j] + 1);
			}
		}
		Max = max(Max, f[i]);
	}
	return Max;
}

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
		}
		int res = 0; 
		int base = solve(-1);
	  	for (int i = 1; i <= n; ++i) {
			if (solve(i) != base) {
				++res;
			}
		}	
		printf("%d\n", res);
	}
	return 0;
}
