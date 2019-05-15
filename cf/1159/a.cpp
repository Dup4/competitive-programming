#include <bits/stdc++.h>
using namespace std;

#define N 110
int n;
char s[N];

int main() {
	while (scanf("%d", &n) != EOF) {
		scanf("%s", s + 1);
		int res = 0;
		for (int i = 1; i <= n; ++i) {
			if (s[i] == '+') {
				++res;
			} else {
				if (res > 0) {
					--res;
				}
			}
		}
		printf("%d\n", res);
	}
	return 0;
}
