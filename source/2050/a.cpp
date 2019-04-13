#include <bits/stdc++.h>
using namespace std;

#define N 100010
char s[N];

bool ok() {
	int len = strlen(s + 1);
	if (len % 4) return false;
	for (int i = 4; i <= len; i += 4) {
		if (s[i - 3] != '2' || s[i - 2] != '0' || s[i - 1] != '5' || s[i] != '0') {
			return false;
		}
	}
	return true;
}

int main() {
	int T; cin >> T;
	while (T--) {
		scanf("%s", s + 1);
		puts(ok() ? "Yes" : "No");
	}
	return 0;
}
