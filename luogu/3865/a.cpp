#include <bits/stdc++.h>
using namespace std;

#define N 100010
#define M 20

struct RMQ {
	int dp[N][M];
	int mm[N];
	void init(int n, int *b) {
		mm[0] = -1;
		for (int i = 1; i <= n; ++i) {
			mm[i] = ((i & (i - 1)) == 0) ? mm[i - 1] + 1 : mm[i - 1];
			dp[i][0] = b[i];
		}
		for (int j = 1; j <= mm[n]; ++j) {
			for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
				dp[i][j] = max(dp[i - 1][j], dp[i + (1 << (j - 1))][j - 1]);
			}
		}
	}
};
