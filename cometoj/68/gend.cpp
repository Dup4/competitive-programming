#include <bits/stdc++.h>
using namespace std;
using ll = long long;
mt19937 rnd(time(0));
int main() {
	int T = 1; cout << T << endl;
	int n = 1e5, m = 1e5; ll k = 1, D = 1e18;
	cout << n << " " << m << " " << k << " " << D << endl;
	for (int i = 1; i <= m; ++i) {
		cout << rnd() << " \n"[i == m];
	}
}
