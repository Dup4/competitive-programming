#include <bits/stdc++.h>
using namespace std;

#define N 1000010
char s[N], t[N];

bool ok() {
	int len1 = strlen(s + 1), len2 = strlen(t + 1);
	if (len1 != len2 + 2) {
		return 0;
	}
	int wa = 0;
	for (int i = 1, j = 1; i <= len1; ++i) {
		if (s[i] == t[j]) {
			++j;
		} else {
			++wa;
		}
	}
	return wa == 2; 
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%s%s", s + 1, t + 1);
		puts(ok() ? "1" : "0");
	}
	return 0;
}
