#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e7 + 10;
char s[N], t[N];

struct ExKMP {
	int Next[N], extend[N];
	void getNext(char *s) {
		int lens = strlen(s + 1), p = 1, pos;
		Next[1] = lens;
		while (p + 1 <= lens && s[p] == s[p + 1]) ++p;
		Next[pos = 2] = p - 1;
		for (int i = 3; i <= lens; ++i) {
			int len = Next[i - pos + 1];
			if (len + i < p + 1) Next[i] = len;
			else {
				int j = max(p - i + 1, 0);
				while (i + j <= lens && s[j + 1] == s[i + j]) ++j;
				p = i + (Next[pos = i] = j) - 1;
			}
		}
	}
	void work(char *s, char *t) {
		int lens = strlen(s + 1), lent = strlen(t + 1), p = 1, pos;
		getNext(t);
		while (p <= lent && s[p] == t[p]) ++p;
		p = extend[pos = 1] = p - 1;
		for (int i = 2; i <= lens; ++i) {
			int len = Next[i - pos + 1];
			if (len + i < p + 1) extend[i] = len;
			else {
				int j = max(p - i + 1, 0);
				while (i + j <= lens && t[j + 1] == s[i + j]) ++j;
				p = i + (extend[pos = i] = j) - 1;
			}
		}
	}
}exkmp;


int main() {
	while (scanf("%s%s", s + 1, t + 1) != EOF) {
		exkmp.work(s, t);
		int lens = strlen(s + 1);
		int lent = strlen(t + 1);
		ll z = 0, p = 0;
//		for (int i = 1; i <= lent; ++i)
//			printf("%d%c", exkmp.Next[i], " \n"[i == lent]);
//		for (int i = 1; i <= lens; ++i)
//			printf("%d%c", exkmp.extend[i], " \n"[i == lens]);
		for (int i = 1; i <= lent; ++i) z ^= 1ll * i * (exkmp.Next[i] + 1);
		for (int i = 1; i <= lens; ++i) p ^= 1ll * i * (exkmp.extend[i] + 1);
		printf("%lld\n%lld\n", z, p);
	}
	return 0;
}