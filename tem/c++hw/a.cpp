#include <bits/stdc++.h>
using namespace std;

#define db double

int main() {
	ifstream in("gpa.dat");
	string name;
	string s;
	db Max = 0, Min = 4;
	while (getline(in, name)) {
		getline(in, s);
		stringstream ss;
		ss << s;
		db a, b, tot = 0;
		db gpa = 0;
		while (ss >> a >> b) {
			tot += a;	
			gpa += a * b;
		}
		gpa /= tot;
		Max = max(Max, gpa);
		Min = min(Min, gpa);
		cout << "GPA for " << name << " = " << fixed << setprecision(2) << gpa << endl;
	}	
	cout << "max GPA = " << fixed << setprecision(2) << Max << endl;
	cout << "min GPA = " << fixed << setprecision(2) << Min << endl;
	return 0;
}
