#include <bits/stdc++.h>
using namespace std;

int main() {
	puts("1");
	int n = 100000;
	cout << n << endl;
	for (int i = 2; i <= n; ++i) {
		printf("%d %d 3\n", i - 1, i);
	}
	return 0;
}
