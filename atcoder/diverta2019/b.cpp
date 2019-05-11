#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 3010
int a[4], n;
ll f[4][N];

int main() {
	while (scanf("%d", a + 1) != EOF) {
		for (int i = 2; i <= 3; ++i) {
			scanf("%d", a + i);
		}
		scanf("%d", &n);
		memset(f, 0, sizeof f);
		f[0][0] = 1;
		for (int i = 1; i <= 3; ++i) {
			for (int j = 0; j <= n; j += a[i]) {
				for (int k = n - j; k >= 0; --k) {
					f[i][k + j] += f[i - 1][k];
				}
			}
		}
		printf("%lld\n", f[3][n]);
	}
	return 0;
}
