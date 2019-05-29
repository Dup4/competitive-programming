#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 200010
int n;
char s[N];

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%s", s + 1);
		n = strlen(s + 1);
		ll res = 0;
		int tmp = 0;
		for (int i = 1; i <= n; ++i) {
			if (s[i] == '9') {
				++tmp; 
			} else {
				tmp = 0;
			}
			if (tmp == 0) {
				++res;
			} else {
				res += tmp;
				if (i - tmp >= 1 && s[i - tmp] != '0') {
					++res;
				}
			}
		}
		printf("%lld\n", res);
	}
	return 0;
}
