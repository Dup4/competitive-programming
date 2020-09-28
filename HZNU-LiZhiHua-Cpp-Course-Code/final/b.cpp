#include <bits/stdc++.h>
using namespace std;

#define db double
db a[3];
int main() {
	while (cin >> a[0]) {
		for (int i = 1; i < 3; ++i) {
			cin >> a[i];
		}
		sort(a, a + 3);
		if (a[0] + a[1] <= a[2]) {
			cout << "Invalid\n";
		} else {
			cout << accumulate(a, a + 3, 0.0) << endl;
		}
	}
	return 0;
}
