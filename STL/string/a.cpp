#include <bits/stdc++.h>
using namespace std;

int main() {
	string s;
	
//	s += "Hangzhou";
//	s += "Normal";
//	s += "University";
//	s += "Hangzhou";
	
//	int x = 2;
//	cout << x << endl;

	//cout << s << endl;
	

//	cout << s << endl;
//	cout << s.find("Hangzhou", 0) << endl;
//	cout << s.substr(0, 8) << endl;


//	s.replace(s.find("Hangzhou"), 8, "hangzhou");
//	cout << s << endl;
	
//	s.replace(s.find("Hangzhou"), 8, 3, 'd');
//	cout << s << endl; 

//	reverse(s.begin(), s.end()); 
//	cout << s << endl;

//	s.replace(s.begin(), s.end(), "");
//	cout << s << endl;

//	s.erase(s.begin());
//	cout << s << endl;

//	s.erase(0, 5);
//	cout << s << endl;

	
	
//	s.erase(s.begin(), s.end());
//
//	cout << s << endl;


//	cin >> s;
//	getline(cin, s);
//	cout << s << endl;

	stringstream ss; 
	getline(cin, s);
	ss << s;
	while (ss >> s) {
		cout << s << endl;
	}	
	
	return 0;
}
