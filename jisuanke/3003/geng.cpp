#include <bits/stdc++.h>
using namespace std;

int main() {
	int T = 20, n = 100000, q = 446;
	cout << T << endl;
	string s = "";
	for (int i = 1; i <= n; ++i) s += 'a';
	while (T--) {
		int sum = 0;
		cout << s << endl;
		cout << q << endl;
		string t = "";
		for (int i = 1; i <= q; ++i) {
			t += 'a';
			sum += t.size();
			cout << t << endl;
		}
		assert(sum <= 100000);
	}
}
