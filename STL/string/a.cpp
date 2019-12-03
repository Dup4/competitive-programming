#include <bits/stdc++.h>
using namespace std;

int main() {
	string s;
	
	s += "Hangzhou";
	s += "Normal";
	s += "University";
	s += "Hangzhou";
	cout << s << endl;
	cout << s.find("Hangzhou", 24) << endl;
	cout << s.substr(0, 8) << endl;

	s.replace(s.find("Hangzhou"), 8, "");
	cout << s << endl;
	s.replace(s.begin(), s.end(), "");
	cout << s << endl;
	//getline(cin, s);
	//cout << s << endl;



	

	
	return 0;
}
