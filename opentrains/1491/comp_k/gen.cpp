#include <bits/stdc++.h>
using namespace std;
mt19937 rnd(time(0));
int main() {
	int T = 3; cout << T << endl;
	while (T--) {
		string s = "", t = "";
		int n = rnd() % 20 + 1, m = rnd() % 100 + 1;
		for (int i = 1; i <= n; ++i) s += rnd() % 2 + 'a';
		cout << s << endl;
		int q = 10;
		cout << q << endl;
		for (int i = 1; i <= q; ++i) {
			m = rnd() % 5 + 1;
			t = "";
			for (int j = 1; j <= m; ++j) t += rnd() % 2 + 'a';
			cout << t << endl;
		}
	}
}
