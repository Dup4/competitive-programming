#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n;
char s[N];

int main() {
	while (scanf("%d", &n) != EOF) {
		scanf("%s", s + 1);
		int need = n - 11;
		int cnt = 0;
		for (int i = 1; i <= n - 10; ++i) {
			if (s[i] == '8') {
				++cnt;
			}
		} 
		if (cnt > need / 2) {
			puts("YES");
		} else {
			puts("NO");
		}
	}
	return 0;
}
