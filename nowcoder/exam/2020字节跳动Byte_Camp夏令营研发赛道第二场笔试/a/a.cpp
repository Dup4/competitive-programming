#include <bits/stdc++.h>
using namespace std;
#define SZ(x) (int(x.size()))
const int N = 1e6 + 10;
int n;
char s[N];
int Mon[2][13] = {
	0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31,
	0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31,
};

map <string, int> mp; 

bool isYeap(int y) {
	if (y == 2004 || y == 2008 || y == 2012 || y == 2016 || y == 2020) return true;
	return false;
//	return (y % 4 == 0);
}

bool ok(int y, int m, int d) {
	if (y < 2001 || y > 2020) return false;
	if (m < 1 || m > 12) return false;
	int Yeap = isYeap(y);
//	cout << Yeap << " " << Mon[Yeap][m] << " " << d << endl;
	if (d < 1 || d > Mon[Yeap][m]) return false;
//	cout << y << " " << m << " " << d << endl;
	return true;
}

inline int toNum(char ch) { return ch - '0'; }

void gao(string d, string m, string y) {
	if (SZ(d) < 2 || SZ(m) != 2 || SZ(y) < 4) return;
   	int _d = toNum(d.end()[-2]) * 10 + toNum(d.end()[-1]);
   	int _m = toNum(m.end()[-2]) * 10 + toNum(m.end()[-1]);
   	int _y = toNum(y[0]) * 1000 + toNum(y[1]) * 100 + toNum(y[2]) * 10 + toNum(y[3]);
	if (ok(_y, _m, _d)) {
		string t = "";
		t += d.end()[-2];
		t += d.end()[-1];
		t += "-";
	//	t += m.end()[-2];
	//	t += m.end()[-1];
		t += m.substr(0, 2);
		t += "-";
		t += y.substr(0, 4);
		++mp[t];
	}
}

int main() {
	scanf("%s", s + 1);
	n = strlen(s + 1);
	string t = "";
	vector <string> vec;
	mp.clear();
	for (int i = 1; i <= n; ++i) {
		if (s[i] == '-') {
			vec.push_back(t);
		//	if (SZ(t) > 0) {
		//		vec.push_back(t);
		//	} 
			t.clear();
		} else {
			t += s[i];
		}
	}
	if (SZ(t) > 0) {
		vec.push_back(t);
	}
	for (int i = 2; i < SZ(vec); ++i) {
		gao(vec[i - 2], vec[i - 1], vec[i]);
	}
	string ans = ""; int Max = -1;
	for (auto &it : mp) {
		if (it.second >= Max) {
			Max = it.second;
			ans = it.first;
		}
	}
	cout << ans << "\n";
	return 0;
}
