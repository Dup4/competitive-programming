#include <bits/stdc++.h>
using namespace std;

int main() {
	string s;

	s += "Hangzhou";
	s += "Normal";
	s += "University";
	s += "Hangzhou";
//	
//	cout << s << endl;
//	cout << s.find("Hangzhou", 24) << endl;
//	cout << s.substr(0, 8) << endl;
//
//	s.replace(s.find("Hangzhou"), 8, "hangzhou");
//	cout << s << endl;
//	
//	s.replace(s.find("Hangzhou"), 8, 3, 'd');
//	cout << s << endl; 
//
//	reverse(s.begin(), s.end()); 
//	cout << s << endl;
//
//	s.replace(s.begin(), s.end(), "");
//	cout << s << endl;

	s.erase(s.begin());
	s.erase(0, 1);

	cout << s << endl;

	s.erase(s.begin(), s.end());

	cout << s << endl;

	//getline(cin, s);
	//cout << s << endl;

//	stringstream ss; 
//	getline(cin, s);
//	ss << s;
//	while (ss >> s) {
//		cout << s << endl;
//	}	




	

	
	return 0;
}
