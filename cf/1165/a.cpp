#include <bits/stdc++.h>
using namespace std;

#define N 200010
char s[N];

int main() {
	int n, x, y;
	while (scanf("%d%d%d", &n, &x, &y) != EOF) {
		scanf("%s", s + 1);
		int res = 0;
		for (int i = n; i >= n - x + 1; --i) {
			if (n - i == y) {
				res += (s[i] == '0');
			} else {
				res += (s[i] == '1');
			}
		}
		printf("%d\n", res);
	}
	return 0;
}
