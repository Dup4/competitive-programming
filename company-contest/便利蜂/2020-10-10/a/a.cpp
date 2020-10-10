#include <bits/stdc++.h>
#define SZ(x) (int(x.size()))
using namespace std;

const int N = 1e6 + 10;
string s;
int n, f[N];

void sp(string s, string &a, string &b) {
	a = "";
	b = "";
	int len = s.size();
	int f = 0;
	for (int i = 0; i < len; ++i) {
		if (!f) a += s[i];
		else b += s[i];
		if (i && s[i] == '>' && s[i - 1] == '-') f = 1;
	}
	if (!a.empty() && a.back() == '>') a.pop_back();
	if (!a.empty() && a.back() == '-') a.pop_back();
}

map <string, string> mp;

bool ok(int l, int r) {
	for (int i = l; i <= r; ++i) {
		if (f[i] != -1)
			return false;
	}
	return true;
}

int main() {
	ios::sync_with_stdio(false); 
	cin.tie(0); cout.tie(0);
	cin >> s;
	mp.clear();
	cin >> n;
	char lc = '!';
	char rc = '?';
	for (int i = 1; i <= n; ++i) {
		string t, a, b;
		cin >> t;
		sp(t, a, b);
		mp[a] = b;
	}
	string t = "";
	for (int i = 0; i < SZ(s); ++i) {
		if (s[i] == '{' && !t.empty() && t.back() == '{') {
			t.pop_back();
			t += lc;
		} else if (s[i] == '}' && !t.empty() && t.back() == '}') {
			t.pop_back();
			t += rc;
		} else {
			t += s[i];
		}
	}
	s = t;
	memset(f, -1, sizeof f);
	stack <int> sta;
	for (int i = 0; i < SZ(t); ++i) {
		if (s[i] == lc) sta.push(i);
		else if (s[i] == rc) {
			if (!sta.empty()) {
				f[i] = sta.top();
				f[sta.top()] = i;
				sta.pop();
			}
		}
	}
	string res = "";
//	int place = 0;
	for (int i = 0; i < SZ(s); ++i) {
		if (f[i] != -1 && f[i] > i) {
			if (ok(i + 1, f[i] - 1)) {
				string tmp = "";
				for (int j = i + 1; j <= f[i] - 1; ++j) {
					tmp += s[j];
				}
				if (tmp.empty()) {
					res += lc;
					res += rc;
				} else {
					if (mp.count(tmp)) res += mp[tmp];
					else res += tmp;
				}
				i = f[i];
			} else {
				res += s[i];	
			}
		} else {
			res += s[i];
		}
	}
	s = res;
	res = "";
	for (int i = 0; i < SZ(s); ++i) {
		if (s[i] == lc) {
			res += "{{";
		} else if (s[i] == rc) {
			res += "}}";
		} else {
			res += s[i];
		}
	}
	cout << res << endl;
	return 0;
}
