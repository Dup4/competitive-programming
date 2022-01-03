#include <bits/stdc++.h>
using namespace std;

int main() {
	int n = 200000, m = 100000;
	cout << n << " " << m << endl;
	for (int i = 2; i <= 100000; ++i) {
		printf("%d %d\n", i - 1, i);
	}
	for (int i = 100001; i <= n; ++i) {
		printf("%d %d\n", 100000, i);
	}
	for (int i = 100001; i <= n; ++i) {
		printf("%d%c", i, " \n"[i == n]);
	}
	return 0;
}
