#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 10, ALP = 26;
char s[N], t[N];
int n, f[N][ALP], nx[ALP];

int main() {
	while (scanf("%s%s", s + 1, t + 1) != EOF) {
		n = strlen(s + 1);
		for (int i = 0; i < ALP; ++i) nx[i] = n + 1;
		for (int i = n; i >= 0; --i) {
			int ch = s[i] - 'a';
			for (int j = 0; j < ALP; ++j) {
				f[i][j] = nx[j];
			}
			if (i) nx[ch] = i;
		}
		int res = 0;
		for (int i = 1, j; i <= n; ++i) {
			int p = 0;
			for (j = i; j <= n; ++j) {
				int ch = t[j] - 'a';
				if (f[p][ch] > n) break;
				p = f[p][ch];
			}
			res = max(res, j - i);
		}
		printf("%d\n", n - res);
	}
	return 0;
}
