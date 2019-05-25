#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, m;
	n = m = 1000;
	printf("%d %d\n", n, m);
	for (int i = 1; i < n; ++i) {
		printf("%d %d %d\n", i, i + 1, 1);
	}
	return 0;
}
