#include <bits/stdc++.h>
using namespace std;

#define N 110
int n, k;
char s[N];

int main() {
	while (scanf("%d%d", &n, &k) != EOF) {
		scanf("%s", s + 1);
		s[k] += 32;
		printf("%s\n", s + 1);
	}
	return 0;
}
