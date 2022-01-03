#include <bits/stdc++.h>
using namespace std;

int main() {
	int n; 
	while (scanf("%d", &n) != EOF) {
		if (n & 1) {
			puts("0");
		} else {
			printf("%lld\n", 1ll << (n / 2));
		}
	}
	return 0;
}
