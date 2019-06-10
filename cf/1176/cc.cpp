#include <bits/stdc++.h>
using namespace std;

int n;
int cnt[110];

int main() {
	while (scanf("%d", &n) != EOF) {
		memset(cnt, 0, sizeof cnt);
		int res = 0;
		for (int i = 1, x; i <= n; ++i) {
			scanf("%d", &x);
			switch (x) {
				case 4 :
					++cnt[4];
					break;
				case 8 :
					if (cnt[4]) {
						--cnt[4];
						++cnt[8];
					}
					break;
				case 15 :
					if (cnt[8]) {
						--cnt[8];
						++cnt[15];
					}
					break;
				case 16 :
					if (cnt[15]) {
						--cnt[15];
						++cnt[16];
					}
					break;
				case 23 :
					if (cnt[16]) {
						--cnt[16];
						++cnt[23];
					}
					break;
				case 42 :
					if (cnt[23]) {
						--cnt[23];
						res += 6;
					}
					break;
				default :
					assert(0);
			}
		}
		printf("%d\n", n - res);
	}
	return 0;
}
