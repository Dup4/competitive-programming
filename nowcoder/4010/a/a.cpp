#include <bits/stdc++.h>
using namespace std;
using db = double;
string s;

int main() {
	string tmp = "aeiouy";
	map <char, int> mp;
	for (auto &ch : tmp) mp[ch] = 1;
	cin >> s;
	int tot = 0;
	int len = s.size();
	db res = 0;
	for (int i = 0; i < len; ++i) {
		for (int j = i; j < len; ++j) {
			++tot;
			int A = 0, B = j - i + 1;
			for (int k = i; k <= j; ++k) {
				if (mp[s[k]]) ++A;
			}
			res += A * 1.0 / B;
		}
	}
	res /= tot;
	cout << res << endl;
	return 0;
}
