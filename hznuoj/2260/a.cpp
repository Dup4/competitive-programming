#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
char s[N];

int main() {
	int _T; scanf("%d\n", &_T);
	while (_T--) {
		scanf("%[^\n]\n", s);
		int n = strlen(s), r = n - 1, l = 0;
		while (r >= 0 && (s[r] < '0' || s[r] > '9')) --r;
		if (r == -1) printf("%s\n", s);
		else {
			l = r;
			while (l > 0 && (s[l - 1] >= '0' && s[l - 1] <= '9')) --l;
			while (l < r && s[l] == '0') ++l;
			for (int i = r; i >= l; --i) {
				if (s[i] == '9') {
					s[i] = '0';
				} else {
					++s[i];
					break;
				}
			}
			for (int i = 0; i < n; ++i) {
				if (i == l && s[i] == '0') printf("1");
				printf("%c", s[i]);
			}
			printf("\n");
		}
	}
	return 0;
}
