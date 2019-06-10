#include <bits/stdc++.h>
using namespace std;

int n, cnt[100], a[] = {4, 8, 15, 16, 23, 42};

int main() {
	while (scanf("%d", &n) != EOF) {
		memset(cnt, 0, sizeof cnt);
		for (int i = 1, x; i <= n; ++i) {
			scanf("%d", &x);
			++cnt[x];
		}
		int Min = 1e9;
		for (auto it : a) {
			Min = min(Min, cnt[it]);
		}
		int res = 0;
		for (auto it : a) {
			res += cnt[it] - Min;
		}
		printf("%d\n", res);
	}
	return 0;
}
