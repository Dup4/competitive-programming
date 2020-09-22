#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
char s[N], t[N];

struct KMP {
	int Next[N];
	void getNext(char *s) {
		int len = strlen(s);
		int i, j;
		i = 0;
		j = Next[0] = -1;
		while (i < len) {
			while (-1 != j && s[i] != s[j]) j = Next[j];
			Next[++i] = ++j;
		}
	}
	void gao(char *s, char *t) {
		int lens = strlen(s), lent = strlen(t);
		int i, j;
		i = j = 0;
		getNext(t);
		while (i < lens) {
			while (-1 != j && s[i] != t[j]) j = Next[j];
			++i, ++j;
			if (j >= lent) {
				printf("%d\n", i - lent + 1);
				j = Next[j];
			}
		}
	}
}kmp;

int main() {
	scanf("%s%s", s, t);
	kmp.gao(s, t);
	int lent = strlen(t);
	for (int i = 1; i <= lent; ++i)
		printf("%d%c", kmp.Next[i], " \n"[i == lent]);
	return 0;
}
