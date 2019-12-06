#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10, mod = 1e9 + 7;
char s[N]; 
int f[110];

int main() {
	while (scanf("%s", s + 1) != EOF) {
		memset(f, 0, sizeof f);
		for (int i = 1; s[i]; ++i) {
			if (s[i] == 'P') {
				++f['P'];
			} else if (s[i] == 'A') {
				f['A'] += f['P'];
			} else {
				f['T'] += f['A'];
			}
			f[s[i]] %= mod;
		}
		printf("%d\n", f['T']);
	}
	return 0;
}
