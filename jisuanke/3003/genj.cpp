#include <bits/stdc++.h>
using namespace std;

int main() {
	int T = 10, n = 300;
	cout << T << endl;
	while (T--) {
		cout << n << endl;
		for (int i = 1; i <= n; ++i)
			cout << 500 << " \n"[i == n];
	}
}
