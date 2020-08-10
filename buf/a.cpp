#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	int n = 1e4, res = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = i + 1; j <= n; ++j) {
			res += __gcd(i, j) == 1;
		}
	}
	cout << res << endl;
	return 0;
}
