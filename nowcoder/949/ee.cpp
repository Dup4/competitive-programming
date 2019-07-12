#include <bits/stdc++.h>
using namespace std;

#define N 10010
int f[10][10][N];
int n, a[N][N];

int main() {
	while (scanf("%d", &n) != EOF) {
		int sum = 0;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				scanf("%d", a[i] + j);
				sum += a[i][j];
			}
		}
		for (int i = 1; i <= n; ++i) 
			for (int j = 1; j <= n; ++j) 
				for (int k = 0; k <= sum; ++k) 
					f[i][j][k] = 0;
		f[1][1][a[1][1]] = 1;
		for (int i = 2; i <= n; ++i) {
			for (int j = a[1][i]; j <= sum; ++j) {
				f[1][i][j] += f[1][i - 1][j - a[1][i]];
			}
			for (int j = a[i][1]; j <= sum; ++j) {
				f[i][1][j] += f[i - 1][1][j - a[i][1]];
			}
		}	
		for (int i = 2; i <= n; ++i) {
			for (int j = 2; j <= n; ++j) {
				for (int k = a[i][j]; k <= sum; ++k) {
					f[i][j][k] += f[i - 1][j][k - a[i][j]];
					f[i][j][k] += f[i][j - 1][k - a[i][j]];
				}
			}
		}
		int res = 0;
		for (int i = 0; i <= sum; ++i) {
			res += (f[n][n][i] != 0);
		}
		printf("%d\n", res);
	}
	return 0;
}
