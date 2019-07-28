#include <bits/stdc++.h>
using namespace std;

#define N 100010
#define M 20
int n, m, a[N];

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
	int query(int x, int y) {
		int k = mm[y - x + 1];
		return max(dp[x][k], dp[y - (1 << k) + 1][k]);
	}
}rmq;


int main() {
	while(scanf("%d%d", &n, &m) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
		}
		rmq.init(n, a);
		int l, r;
		while (m--) {
			scanf("%d%d", &l, &r);
			printf("%d\n", rmq.query(l, r));
		}
	}
	return 0;
}
