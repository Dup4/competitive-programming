#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
int n, a[N][5];
ll f[N][32];

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) 
			for (int j = 0; j < 5; ++j)
				scanf("%d", a[i] + j);
		memset(f, 0, sizeof f);
		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j < 1 << 5; ++j) {
				f[i][j] = max(f[i][j], f[i - 1][j]);
				for (int k = 0; k < 5; ++k) {
					if (((j >> k) & 1) == 0) {
						f[i][j | (1 << k)] = max(f[i][j | (1 << k)], f[i - 1][j] + a[i][k]);
					}
				}
			}
		}
		printf("%lld\n", f[n][31]);
	}
	return 0;
}
