#include <bits/stdc++.h>
using namespace std;

int main() {
	int x = 59964251;
	for (int i = 2; i <= x; ++i) {
		while (x % i == 0) {
			cout << i << endl;
			x /= i;
		}
	}
	return 0;
}
