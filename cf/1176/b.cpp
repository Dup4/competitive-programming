#include <bits/stdc++.h>
using namespace std;

#define N 110
int n, cnt[5];

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		memset(cnt, 0, sizeof cnt);
		scanf("%d", &n);
		for (int i = 1, x; i <= n; ++i) {
			scanf("%d", &x);
			++cnt[x % 3];
		}
		int res = cnt[0];
		int tmp = min(cnt[1], cnt[2]);
		res += tmp;
		cnt[1] -= tmp;
		cnt[2] -= tmp;
		res += cnt[1] / 3 + cnt[2] / 3;
		printf("%d\n", res);
	}
	return 0;
}
