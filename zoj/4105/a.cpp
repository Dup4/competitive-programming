#include <bits/stdc++.h>
using namespace std;

#define N 110
char s[N];

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%s", s + 1);
		for (int i = 1, len = strlen(s + 1); i <= len; ++i) {
			bool flag = true;
			for (auto c : {'a', 'e', 'i', 'o', 'u', 'y'}) {
				if (s[i] == c) {
					flag = false;
					break;
				}
			}
			if (flag || i == 1) {
				putchar(s[i]);
			}
		}
		puts("");
	}
	return 0;
}
