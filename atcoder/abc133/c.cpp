#include <bits/stdc++.h>
using namespace std;

#define p 2019

int main() {
	int l, r;
	while (scanf("%d%d", &l, &r) != EOF) {
		if (r - l + 1 >= 3000) {
			puts("0");
			continue;
		} else {
			int res = 1e9;
			for (int i = l; i <= r; ++i) {
				for (int j = l; j < i; ++j) {
					res = min(res, (i % p) * (j % p) % p);
				}
			}
			printf("%d\n", res);
		}
	}
	return 0;
}
