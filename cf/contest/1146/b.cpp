#include <bits/stdc++.h>
using namespace std;

#define N 100010
char s[N];

void solve() {
	int len = strlen(s + 1);
	int pos = 0;
	for (int i = len; i >= 1; --i) {
		if (s[i] == 'a') {
			pos = i;
			break;
		}
	}
	string a = "", b = "", res = "";
	for (int i = 1; i <= pos; ++i) {
		res += s[i];
	}
	for (int i = 1; i <= pos; ++i) if (s[i] != 'a') {
		a += s[i];
	}
	for (int i = pos + 1; i <= len; ++i) {
		b += s[i];
	}
	for (int i = pos + 1; i <= len + 1; ++i) {
		if (a == b) {
			cout << res << "\n";
			return;
		} else {
			if (i == len + 1) {
				break;
			}
			a += s[i];
			res += s[i]; 
			b.erase(0, 1);
		}
	}
	puts(":(");
}

int main() {
	while (scanf("%s", s + 1) != EOF) {
		solve();
	}
	return 0;
}
