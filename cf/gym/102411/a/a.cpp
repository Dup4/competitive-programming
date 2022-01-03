#include <bits/stdc++.h>
using namespace std;
int ceil(int x, int y) {
	return (x + y - 1) / y;
}

int main() {
	int a, b, n;
	while (scanf("%d%d%d", &a, &b, &n) != EOF) {
		int res = ceil(n - b, b - a) + ceil(n - a, b - a);
		printf("%d\n", res);
	}
	return 0;
}
