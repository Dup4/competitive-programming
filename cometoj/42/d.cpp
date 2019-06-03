#include <bits/stdc++.h>
using namespace std;

int cnt[20];

int main() {
	memset(cnt, 0, sizeof cnt);
	for (int i = 1, x; i <= 18; ++i) {
		scanf("%d", &x);
		++cnt[x];
	}
	int res = cnt[0];
	for (int i = 1; i <= 13; ++i) {
		if (cnt[i] == 2 || cnt[i] == 4) {
			cnt[i] = 0;
		} else if (cnt[i] == 3) {
			cnt[i] -= 2;
		}
		res += cnt[i];
	}
	printf("%d\n", res);
	return 0;
}
