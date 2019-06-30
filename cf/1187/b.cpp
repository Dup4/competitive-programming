#include <bits/stdc++.h>
using namespace std;

#define N 200010
int n, m, lens, lent;
char s[N], t[N];
int sum[N][27];
int cnt[27];

bool ok(int x) {
	for (int i = 0; i < 26; ++i) {
		if (sum[x][i] < cnt[i]) {
			return 0;
		}
	}
	return 1;
}

int main() {
	while (scanf("%d", &n) != EOF) {
		memset(sum, 0, sizeof sum);
		scanf("%s", s + 1); lens = strlen(s + 1);
		for (int i = 1; i <= lens; ++i) {
			++sum[i][s[i] - 'a'];
			for (int j = 0; j < 26; ++j) {
				sum[i][j] += sum[i - 1][j];
			}
		}
		scanf("%d", &m);
		while (m--) {
			scanf("%s", t + 1);  lent = strlen(t + 1);
			memset(cnt, 0, sizeof cnt);
			for (int i = 1; i <= lent; ++i) {
				++cnt[t[i] - 'a'];
			}
			int l = 1, r = n, res = -1;
			while (r - l >= 0) {
				int mid = (l + r) >> 1;
				if (ok(mid)) {
					r = mid - 1;
					res = mid;
				} else {
					l = mid + 1;
				}
			}
			printf("%d\n", res);
		}
	}
	return 0;
}
