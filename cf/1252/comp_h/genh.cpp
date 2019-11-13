#include <bits/stdc++.h>

using namespace std;

int main() {
	int n = 1000;
	cout << n << endl;
	for (int i = 1; i <= n; ++i) {
		int x = rand() % 1000 + 1, y = rand() % 1000 + 1;
		cout << x << " " << y << endl;
	}
	return 0;
}
