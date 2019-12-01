#include <bits/stdc++.h>

using namespace std;

int n, k;
map<string, int> mp;

bool ok(const string &s) {
	for (int i = 0, len = s.length(), j = len - 1; i < len; ++i, --j) {
		if (s[i] != s[j]) return false;
	}
	return true;
}

bool check(const string &s) {
	string pre, suf;
	for (int o = 0, len = s.length(); o < len; ++o) {
		pre.clear(), suf.clear();
		for (int i = 0; i < o; ++i) pre += s[i];
		for (int i = o; i < len; ++i) suf += s[i];
		if (ok(pre) && ok(suf)) return true;
	}
	return false;
}

void gao(const string &s) {
	if (s.length() == n) {
		if (check(s)) {
		   	mp[s]++;
		}
		return ;
	}
	if (check(s)) mp[s]++;
	for (int i = 1; i <= k; ++i) {
		string t = s;
		t += 'a' + i - 1;
		gao(t);
	}
}

int main() {
	for (n = 1; n <= 10; ++n) for (k = 1; k <= 6; ++k) {
		mp.clear();
		gao("");
		cout << n << " " << k << " " << mp.size() << endl;
	}
	return 0;
}
