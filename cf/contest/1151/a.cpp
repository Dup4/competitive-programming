#include <bits/stdc++.h>
using namespace std;

int n;
char s[110];

int f(char x, char y) {
	if (x == y) {
		return 0;
	} else {
		if (x < y) swap(x, y);
		return min(x - y, 'Z' - x + y - 'A' + 1);
	}
}

int work() {
	int res = 1e9;
	for (int i = 1; i <= n - 3; ++i) {
		res = min(res, f(s[i], 'A') + f(s[i + 1], 'C') + f(s[i + 2], 'T') + f(s[i + 3], 'G'));
	}
	return res;
}

int main() {
	while (scanf("%d", &n) != EOF) {
		scanf("%s", s + 1);
		printf("%d\n", work());
	}
	return 0;
}
