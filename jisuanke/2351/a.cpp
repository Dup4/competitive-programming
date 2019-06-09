#include <bits/stdc++.h>
using namespace std;

#define N 1000010
char s[N];

bool ok1() {
	int len = strlen(s + 1);
	for (int i = 1; i <= len / 2; ++i) {
		if (s[i] == s[len - i + 1]) {
			return false;
		}
	}
	return true;
}

bool ok2() {
	int l = 0, len = strlen(s + 1);
	for (int i = 1; i <= len; ++i) {
		if (s[i] == '(') {
			++l;
		} else {
			if (!l) {
				return false;
			}
			--l;
		}
	}
	return l == 0;
}

int main() {
	while (scanf("%s", s + 1) != EOF) {
		puts(ok1() && ok2() ? "YES" : "NO");
	}
	return 0;
}
