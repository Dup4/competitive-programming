#include <bits/stdc++.h>
using namespace std;
mt19937 rnd(time(0));
int random(int l, int r) { return rnd() % (r - l + 1) + l; }

int main() {
	int _T = 1;
	cout << _T << endl;
	int n = 1e6, p = 1e9, q = 2e7;
	cout << n << " " << p << " " << q << endl;
	for (int i = 1; i <= n; ++i)
		cout << random(1, 1e9) << " \n"[i == n];
	int m = (q / 64) + 2;
	for (int i = 1; i <= m; ++i)
		cout << random(1, n) << " \n"[i == n];
}
