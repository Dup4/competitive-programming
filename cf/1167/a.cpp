#include <bits/stdc++.h>
using namespace std;

#define N 110
int n;
char s[N];

bool ok() {
	for (int i = n - 10; i >= 1; --i) {
		if (s[i] == '8') {
			return true;
		}
	}
	return false;
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		scanf("%s", s + 1);
		puts(ok() ? "YES" : "NO");
	}
	return 0;
}
