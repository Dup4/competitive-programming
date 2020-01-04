#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, m; cin >> n >> m;
	string s;
	int res = 0;
	for (int i = 1; i <= n; ++i) {
		cin >> s;
		if (s[0] == 'w') ++res;
		for (int j = 1; j < m; ++j) {
			if (s[j - 1] == '.' && s[j] == 'w')
				++res;
		}
	}
	cout << res << endl;
	return 0;
}
