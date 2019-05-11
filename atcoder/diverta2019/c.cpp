#include <bits/stdc++.h>
using namespace std;

int n;
char s[110];
int cnt[3];

int main() {
	while (scanf("%d", &n) != EOF) {
		memset(cnt, 0, sizeof cnt);
		int res = 0;
		for (int i = 1; i <= n; ++i) {
			scanf("%s", s + 1);
			int len = strlen(s + 1); 
			for (int j = 1; j < len; ++j) {
				if (s[j] == 'A' && s[j + 1] == 'B') {
					++res;
				}
			}
			if (s[1] == 'B' && s[len] == 'A') {
				++cnt[0];
			} else if (s[1] == 'B') {
				++cnt[1];
			} else if (s[len] == 'A') {
				++cnt[2]; 
			}
		}
		if (cnt[0]) {
			res += cnt[0] - 1;
			cnt[0] = min(cnt[0], 1);
			if (cnt[1]) {
				++res;
				--cnt[1];
			}
			if (cnt[2]) {
				++res;
				--cnt[2];
			}
		}
		res += min(cnt[1], cnt[2]);
		printf("%d\n", res);
	}
	return 0;
}
