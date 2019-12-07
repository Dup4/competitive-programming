#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll x;
string s;

int main() {
	int _T; cin >> _T;
	while (_T--) {
		cin >> s;
		ll x = 0, A = 0, B = 0;
		for (int i = 0, len = s.size(); i < len; ++i) {
			int c = s[i] - '0';
			x = x * 10 + c;
			if (i < len / 2) {
				A = A * 10 + c;
			} else {
				B = B * 10 + c;
			}
		}
		if (A == 0 || B == 0) puts("No");
		else {
			if (x % A == 0 && (x / A) % B == 0) {
				puts("Yes");
			} else {
				puts("No");
			}
		}	
	}
	return 0;
}
