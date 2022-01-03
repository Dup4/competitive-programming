#include <bits/stdc++.h>
using namespace std;

string s, res;

bool ok(string &s) {
	for (int i = 1, len = (int)s.size(); i < len; ++i) {
		if (abs(s[i] - s[i - 1]) == 1) {
			return false;
		}
	}
	return true;
}

void solve() {
	res = "";
	for (int len = (int)s.size(), i = 0, j = len / 2; i < len / 2 || j < len; ++i, ++j) {
		if (j < len) {
			res += s[j];
		} 
		if (i < len / 2) {
			res += s[i];
		}
	}
	if (ok(res)) {
		cout << res << "\n";
	} else {
		cout << "No answer\n";
	}
}

int main() {
	ios::sync_with_stdio(false);
	int T; cin >> T; 
	while (T--) {
		cin >> s;
		sort(s.begin(), s.end());
		solve();
	}
	return 0;
}

