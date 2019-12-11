#include <bits/stdc++.h>
using namespace std;
void gao(string &s) {
	if (s.size() >= 4 && s.substr(s.size() - 4, 4) == " is ") {
		s.erase(s.size() - 4, 4);
		s += " was ";
	}
}
int main() {
	string s; 
	getline(cin, s);
	string t = "";
	for (auto &c : s) {
		t += c;
		gao(t);
	}
	cout << t << "\n";
	return 0;
}
