#include <bits/stdc++.h>
using namespace std;

int main() {
	int ans = 0;
	for (int i = 1; i <= 100; ++i) {
		ans ^= i;
		printf("%d %d\n", i, ans);
	}
	return 0;
}
