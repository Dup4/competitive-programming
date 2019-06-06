#include <bits/stdc++.h>
using namespace std;

#define db double
db a[] = {
	28.9,
	32.7,
	45.6,
	78,
	35,
	86.2,
	27.8,
	43,
	56,
	65
};

int main() {
	int n = 10;
	int T; cin >> T;
	while (T--) {
		db res = 0;
		for (int i = 0, x; i < n; ++i) {
			cin >> x;
			res += x * a[i];
		}
		cout << fixed << setprecision(2) << res << "\n";
	}	
	return 0;
}
