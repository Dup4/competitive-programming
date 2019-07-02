#include <bits/stdc++.h>
using namespace std;

#define N 1000010
char s[N], t[N], sta[N];
int cnt[N], top;
int n, k;

void work(char *s) {
	memset(cnt, 0, sizeof cnt);
	top = 0; 
	for (int i = 1; i <= n; ++i) {
		if (top == 0) {
			sta[++top] = s[i];
			cnt[top] = 1;
		} else {
			if (sta[top] == s[i]) {
				cnt[top + 1] = cnt[top] + 1;
			} else {
				cnt[top + 1] = 1;
			}
			sta[++top] = s[i]; 
		}
		if (cnt[top] == k) {
			top -= k; 
		}
	}
	for (int i = 1; i <= top; ++i) {
		s[i] = sta[i]; 
	}
	s[top + 1] = 0;
}

int main() {
	while (scanf("%d%d", &n, &k) != EOF) {
		scanf("%s%s", s + 1, t + 1);
		work(s); work(t);
		puts(strcmp(s + 1, t + 1) == 0 ? "Yes" : "No");
	}
	return 0;
}
