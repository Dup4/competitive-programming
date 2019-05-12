#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1 << 17;

int f[MAXN], p[MAXN], dp[MAXN][2];

int main() {
	int n, k;
	scanf("%d", &k);
	n = (1 << k) - 1;
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &f[i]);
		if (i > n / 2) dp[i][0] = dp[i][1] = 1;
		//p[i]=0;
	}
//	for (int i = n; i > 1; --i) {
//		if (p[i] == 0) {
//			if (p[i / 2] == 0 && f[i] != f[i / 2]) {
//				p[i] = 1; p[i / 2] = 1;
//				f[i] = 1; f[i / 2] = 0;
//			}
//			else f[i] = 1;
//		}
//	}
	for (int i = n / 2; i > 0; --i) {
		dp[i][0] = 1 + min(dp[2 * i][0], dp[2 * i][1]) + min(dp[2 * i + 1][0], dp[2 * i + 1][1]);
		dp[i][1] = min(dp[2 * i][0] + (f[i] == f[2 * i]) + min(dp[2 * i + 1][0], dp[2 * i + 1][1]), 
					   dp[2 * i + 1][0] + (f[i] == f[2 * i + 1]) + min(dp[2 * i][0], dp[2 * i][1]));
	}
//	int ans = 0;
//	for (int i = 1; i <= n; ++i)
//		if (f[i] == 1) ++ans;
	printf("%d\n", min(dp[1][0], dp[1][1]));
	return 0;
}
