#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, d;
	while (cin >> n >> d) {
		d = 2 * d + 1;
		n = n / d + (n % d != 0);
		cout << n << "\n";
	}
	return 0;
}
