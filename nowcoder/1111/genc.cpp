#include <bits/stdc++.h>
using namespace std;

mt19937 rnd(time(0));
int main() {
	int n = 100000, m = 100000;
	cout << n << " " << m << endl;
	for (int i = 1; i <= m; ++i) {
		cout << rnd() % n + 1 << " " << rnd() % n + 1 << " " << rnd() % 10000 + 1 << endl;
	}
	return 0;
}
