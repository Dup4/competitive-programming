#include <bits/stdc++.h>
using namespace std;

int main() {
	srand(time(NULL));
	int n = 1e9, q = 1e6;
	printf("%d %d\n", n, q);
	for (int i = 1; i <= q; ++i) {
		printf("%d %d\n", rand() % 2 + 1, rand() % n + 1);
	}
	return 0;
}
