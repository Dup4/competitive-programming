#include <bits/stdc++.h>
using namespace std;

int main() {
	string s;
	while (cin >> s) {
		int tot = 0;
		int remind = 15 - (int)s.size();
		for (auto it : s) {
			tot += (it == 'o');
		}
		puts((tot + remind >= 8) ? "YES" : "NO");
	}
	return 0;
}
