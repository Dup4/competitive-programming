#include <bits/stdc++.h>
using namespace std;
string s, t;
void gao() {
	int ls = s.size(), lt = t.size(), cnt = 0;
	for (int i = 0; i < lt - ls + 1; ++i) {
		if (t.substr(i, ls) == s) {
			++cnt;
			if (cnt >= 3) {
				cout << "YOUR ARE CP!" << endl;
				return;
			}
			i += ls;
		   	--i;	
		}
	}
	cout << "YOU JUST A SINGLE DOG!" << endl;
}

int main() {
	int _T; cin >> _T;
	while (_T--) {
		cin >> s >> t;
		gao();
	}
	return 0;
}
