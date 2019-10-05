#include <bits/stdc++.h>
using namespace std;

mt19937 rnd(time(0));

int main() {
	int T = 10;
	while (T--) {
		int n = 300, m = n * (n - 1) / 2, q = 300;
		cout << n << " " << m << " " << q << endl;
		for (int i = 1; i <= n; ++i)
			for (int j = i + 1; j <= n; ++j)
				cout << i << " " << j << endl;
		while (q--) cout << n << endl;
	}
	return 0;
}
