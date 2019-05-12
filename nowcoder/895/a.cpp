#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 10010
char s[N];

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%s", s + 1);
		ll res = 0;
		for (int i = 2; i <= 10; ++i) {
			ll tot = 0;
			for (int j = 1, len = strlen(s + 1); j <= len; ++j) {
				tot = tot * i + s[j] - '0';
			}
			res += tot;
		}
		printf("%lld\n", res);
	}
	return 0;
}
