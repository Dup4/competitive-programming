#include <bits/stdc++.h>
using namespace std;

#define N 200010
char s[N];
int a[20];

int main() {
	while (scanf("%s", s + 1) != EOF) {
		memset(a, 0, sizeof a);
		for (int i = 1, len = strlen(s + 1); i <= len; ++i) {
			++a[s[i] - '0'];
		}
		printf("%d\n", min(a[1] / 3, min(a[4] / 2, a[5])));
	}
	return 0;
}
