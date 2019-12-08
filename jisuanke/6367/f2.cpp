#include <bits/stdc++.h>
using namespace std;

int main() {
	int res = 0;
	for (int i = 0; i <= 200; ++i) {
		long long x, y, z;
		cin >> x >> y >> z;
		if (x == -12345678) {
			cout << "\"impossible\",";
			++res;
		} else {
			assert(abs(x) <= 5000 && abs(y) <= 5000 && abs(z) <= 5000 && x * x * x + y * y * y + z * z * z == i);
			cout << "\"";
			cout << x << " " << y << " " << z << "\",";
		}
		cout << endl;
	}
	cout << res << endl;
	return 0;
}
