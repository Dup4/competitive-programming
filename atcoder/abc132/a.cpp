#include <bits/stdc++.h>
using namespace std;

int main() {
	string s; cin >> s;
	sort(s.begin(), s.end());
	s.erase(unique(s.begin(), s.end()), s.end());
	cout << (((int)s.size() == 2) ? "Yes" : "No") << "\n";
	return 0;
}
