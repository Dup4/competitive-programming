#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e3 + 10;

int n, m, k;
double p[maxn];
double dp[maxn][maxn];

int main() {
	while(~scanf("%d %d %d", &n, &m, &k)) {
		memset(dp, 0, sizeof dp);
		for (int i = 1; i <= m; ++i) p[i] = 1.0;
		for (int i = 1, a; i <= n; ++i) {
			double pi;
			scanf("%d %lf", &a, &pi);
			p[a] *= (1 - pi);
		}
		dp[0][0] = 1.0;
		for (int i = 1; i <= m; ++i) {
			dp[i][0] = dp[i - 1][0] * p[i]; 
			for (int j = 1; j <= m; ++j) {
				dp[i][j] = dp[i - 1][j] * p[i] + dp[i - 1][j - 1] * (1.0 - p[i]);
			}
		}
		double ans = 0.0;
		for (int i = k; i <= m; ++i) ans += dp[m][i];
		printf("%.3f\n", ans);
	}
	return 0;
}
