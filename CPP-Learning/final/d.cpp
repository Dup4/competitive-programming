#include <bits/stdc++.h>
using namespace std;

#define db double
db PI = acos(-1.0);

int main() {
	int a; cin >> a;
	db x = cos((50.0 / 180) * PI) + sqrt(37.5);
	cout << fixed << setprecision(2) << x / (a + 1) << endl;
	return 0;
}
