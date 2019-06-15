#include <bits/stdc++.h>
using namespace std;

int n, k;

int main() {
	while (scanf("%d%d", &n, &k) != EOF) {
		if (k == 1) {
			puts("0");
		} else {
			printf("%d\n", n - k);
		}
	}
	return 0;
}
