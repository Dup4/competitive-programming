#include <bits/stdc++.h>
using namespace std;

#define N 10010
int n, m, k;
int cnt[N], a[N];

int main() {
	int T; cin >> T;
	while (T--) {
		memset(cnt, 0, sizeof cnt); 
		scanf("%d%d%d", &n, &m, &k);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			++cnt[a[i]];
		}
		for (int i = 1; i <= m; ++i) {
			cnt[i] /= k;
		}
		int res = 0;
		for (int i = 1, sze = n / 2; i <= sze; ++i) {
			if (cnt[a[i]]) {
				++res;
				--cnt[a[i]];
			}
		}
		printf("%d\n", res);
	}
	return 0;
}
