#include <bits/stdc++.h>
using namespace std;

string get(int num) {
	string t = "";
	if (num <= 3) t += string(num, '6');
	else if (num <= 9) t += '9';
	else t += "27";
	return t;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	string s; 
	getline(cin, s);
	string t = "";
	int num = 0;
	for (auto &ch : s) {
		if (ch == '6') {
			++num;
		} else {
			t += get(num);
			t += ch;
			num = 0;
		}
	}
	t += get(num);
	cout << t << endl;
	return 0;
}
