#include <bits/stdc++.h>
using namespace std;
stringstream ss;
string s;
int res;

int getNum() {
	int res = 0;
	for (auto &c : s)
		res = res * 10 + c - '0';
	return res;
}

int dfs() {
	if (!(ss >> s)) return 0;
	if (s == "#") return 0;
	int num = getNum();
	int cnt = dfs() + dfs();
	if (cnt == 2) res += num;	
	return 1;
}

int main() {
	getline(cin, s);
	ss << s;
	res = 0;
	dfs();
	cout << res << "\n";
	return 0;
}
