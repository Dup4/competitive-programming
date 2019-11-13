#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

int r[N];

int main() {
	int n = rand() % 1000 + 1, m = rand() % 1000 + 1, q = rand() % 1000 + 1;
	cout << n << " " << m << " " << q << endl;
	for (int i = 1; i <= n; ++i) {
		cout << rand() % 10000 << " \n"[i == n];
	}
	for (int i = 1; i <= m; ++i) {
		r[i] = rand() % (n - 1) + 1;
		cout << r[i];
		for (int j = 1; j <= r[i]; ++j) {
			cout << " " << rand() % 10000;
		}
		cout << endl;
	}
	for (int i = 1; i <= q; ++i) {
		int x = rand() % m + 1;
		int y = rand() % r[x] + 1;
		int z = rand() % 10000;
		cout << x << " " << y << " " << z << endl;
	}
	return 0;
}
