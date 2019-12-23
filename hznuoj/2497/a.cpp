#include <bits/stdc++.h>
using namespace std;
string s;
bool ok() {
	stack <char> sta;
	for (auto &c : s) {
		if (c == '(') {
			sta.push(c);
		} else if (c == '[') {
			sta.push(c);
		} else if (c == ')') {
			if (!sta.empty() && sta.top() == '(') {
				sta.pop();
			} else {
				return false;
			}
		} else {
			if (!sta.empty() && sta.top() == '[') {
				sta.pop();
			} else {
				return false;
			}
		}
	}	
	return sta.empty(); 
}

int main() {
	cin >> s;
	puts(ok() ? "Match" : "Not Match");
	return 0;
}
