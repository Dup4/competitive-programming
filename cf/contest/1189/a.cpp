#include <bits/stdc++.h>
using namespace std;

#define N 1100
char s[N]; int n;

int main() {
	while (scanf("%d%s", &n, s + 1) != EOF) {
		int cnt = 0;
		for (int i = 1; i <= n; ++i) {
			if (s[i] == '1') ++cnt;
			else --cnt;
		}  
		if (cnt) {
			puts("1"); puts(s + 1);
		} else {
			puts("2");
			printf("%c %s\n", s[1], s + 2);
		}
	}
	return 0;
}
