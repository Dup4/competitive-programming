#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e3 + 10, M = 12;
int n, m1, m2; ll a[N][N];

void add(int x1, int y1, int x2, int y2, int w) {
	a[x1][y1] += w;
	a[x1][y2 + 1] -= w;
	a[x2 + 1][y1] -= w;
	a[x2 + 1][y2 + 1] += w;
}

struct RMQ {
	ll Max[N][M];
	int mm[N];
	void init(int n, ll *b) {
		mm[0] = -1;
		for (int i = 1; i <= n; ++i) {
			mm[i] = ((i & (i - 1)) == 0) ? mm[i - 1] + 1 : mm[i - 1];
			Max[i][0] = b[i];
		}
		for (int j = 1; j <= mm[n]; ++j) {
			for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
				Max[i][j] = max(Max[i][j - 1], Max[i + (1 << (j - 1))][j - 1]);
			}
		}
	}
	ll queryMax(int x, int y) {
		int k = mm[y - x + 1];
		return max(Max[x][k], Max[y - (1 << k) + 1][k]);
	}
}rmq;

int main() {
	while (scanf("%d%d%d", &n, &m1, &m2) != EOF) {
		memset(a, 0, sizeof a);
		for (int i = 1, x[2], y[2], w; i <= m1; ++i) {
			scanf("%d%d%d%d%d", x, y, x + 1, y + 1, &w);
			add(x[0], y[0], x[1], y[1], w);	
		}
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				a[i][j] += a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
			}
		}
		for (int i = 1; i <= n; ++i) rmq[i].init(n, a[i]);
		for (int i = 1, x[2], y[2]; i <= m2; ++i) {
			scanf("%d%d%d%d", x, y, x + 1, y + 1);
			ll ans = 0;
			for (int j = x[0]; j <= x[1]; ++j) {
				ans = max(ans, rmq[j].queryMax(y[0], y[1]));
			}
			printf("%lld\n", ans);
		}	
	}
	return 0;
}